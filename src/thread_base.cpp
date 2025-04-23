#include "thread_base.h"

ThreadBase::ThreadBase(Data& data, int from, int to)
    : data(data), from(from), to(to) {

}


int ThreadBase::compute_t_local() {
    // Обчислення1: ti = min(Zn)
    int tLocal = std::numeric_limits<int>::max();
    for (int i = from; i <= to; ++i) {
        tLocal = std::min(data.Z[i], tLocal);
    }
    return tLocal;
}

void ThreadBase::compute_local_to_data_t(int tLocal) {
    // Обчислення2: t = min(t, ti) - КД1
    pthread_mutex_lock(&data.mutex_t);
    data.t = std::min(data.t, tLocal);
    pthread_mutex_unlock(&data.mutex_t);
}

void ThreadBase::safe_copy_ti() {
    // Копіювання ti = t - КД2
    pthread_mutex_lock(&data.mutex_t);
    ti = data.t;
    pthread_mutex_unlock(&data.mutex_t);

}

void ThreadBase::safe_copy_ei() {
    // Копіювання ei = e - КД3
    pthread_mutex_lock(&data.mutex_e);
    ei = data.e;
    pthread_mutex_unlock(&data.mutex_e);
}

void ThreadBase::compute_An_local() {
    // Обчислення3: An = ti*(B*MVn) + ei*X*(MM*MCn)

    // зберігаємо константні референс на B:
    // копіювати цілий вектор - занадто дорога операція, а референсом ми уберігаємо себе від цього
    // також, оскільки наш референс константний, ми не можемо ніяк мутувати вектор B,
    // додатково забезпечуючи гарантії безпеки від одночасного читання/запису

    const auto& B_local = data.B;
    const auto& B_MVn = Data::multiplyVectorByMatrixRange(B_local, data.MV, from, to);
    const auto& ti_BM_Vn = Data::multiplyByScalar(B_MVn, ti);
    const auto& left = ti_BM_Vn;

    const auto& MM_local = data.MM;
    const auto& X_local = data.X;
    const auto& MM_MCn = Data::multiplyMatrixByMatrixRange(MM_local, data.MC, from, to);

    // TODO: create function when matrix is smaller then vector
    const auto& X_MM_MCn = Data::multiplyVectorByMatrixPart(X_local, MM_MCn);
    const auto& e_X_MM_MCn = Data::multiplyByScalar(X_MM_MCn, ei);
    const auto& right = e_X_MM_MCn;

    const auto& result_from_to = Data::addVectors(left, right);

    // Збереження результату
    for (int i = from; i <= to; ++i) {
        data.A[i] = result_from_to[i - from];
    }
}

void ThreadBase::run_thread() {
    pre_execute();
    execute();
    post_execute();
}

void ThreadBase::execute() {
    // Введення даних
    input();

    // Синхронізація введення для всіх потоків B1
    pthread_barrier_wait(&data.barrier1);

    // Обчислення
    auto tLocal = compute_t_local();
    compute_local_to_data_t(tLocal);

    after_compute_t_sync();

    safe_copy_ti();
    safe_copy_ei();

    compute_An_local();
    after_compute_An_sync();
} 