#pragma once

template <class T>
void swap(T* a, T* b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template<class T>
T rotate(T first, T n_first, T last) {
    if(first == n_first) {
        return last;
    }
    if(n_first == last) {
        return first;
    }
    T read      = n_first;
    T last_read    = first;
    T next_read = first;
 
    while(read != last) {
        if(last_read == next_read) { 
            next_read = read;
        }
        swap(last_read++, read++);
    }
 
    rotate(last_read, next_read, last);
    return last_read;
}

template <class T>
int lower_bound(T* first, int len, const T& value) {
    for (int i = 0; i < len; ++i) {
        if (first[i] >= value) {
            return i;
        }

    }
    return 0;
}

template <class T>
int upper_bound(T* first, int len, const T& value) {
    for (int i = 0; i < len; ++i) {
        if (first[i] > value) {
            return i;
        }
    }
    return 0;
}

template <class T>
void inplace_merge(T* begin, int mid, int end) {
    if (mid == 0 || end == 0) {
        return;
    }
    if (mid == 1 && end == 1) {
        if (begin[0] > begin[1]) {
            swap(begin, begin + 1);
        }
        return;
    }
    if (mid >= end) {
        T x = begin[mid / 2];
        int ind_lb = lower_bound(begin + mid, end, x);
        if (begin[mid + ind_lb] < x) {
            rotate(begin + mid / 2, begin + mid, begin + mid + end);
            inplace_merge(begin, mid / 2, end);
        } else {
            rotate(begin + mid / 2, begin + mid, begin + mid + ind_lb);
            inplace_merge(begin, mid / 2, ind_lb);
            inplace_merge(begin + mid / 2  + ind_lb, mid - mid / 2, end - ind_lb);
        }
        return;
    }else {
        T x = begin[mid + end / 2];
        int ind_ub = upper_bound(begin, mid, x);
        if (begin[ind_ub] <= x) {
            inplace_merge(begin, mid, end / 2);
        } else {
            rotate(begin + ind_ub, begin + mid, begin + mid + end / 2);
            inplace_merge(begin, ind_ub, end / 2);
            inplace_merge(begin + ind_ub + end / 2, mid - ind_ub, end - end / 2);
        }
        return;
    }
}

template <class T>
void inplace_merge_sort(T* data, int N) {
    if (N < 2) {
        return;
    }
    int l = N / 2;
    int r = N - l;
    inplace_merge_sort(data, l);
    inplace_merge_sort(data + l, r);
    inplace_merge(data, l, r);
}