import ctypes

arr_lib = ctypes.CDLL('libarr.so')

_arr_fill_with_fib = arr_lib.arr_fill_with_fib
_arr_fill_with_fib.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t)

_arr_move_first_occurrance = arr_lib.arr_move_first_occurrance
_arr_move_first_occurrance.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_size_t), ctypes.POINTER(ctypes.c_int), ctypes.c_size_t)

def arr_fill_with_fib(nmemb):
    arr = (ctypes.c_int * nmemb)()
    _arr_fill_with_fib(arr, nmemb)
    return list(arr)

def arr_move_first_occurrance(arr):
    pylen = len(arr)
    src_len = ctypes.c_size_t(pylen)
    src = (ctypes.c_int * pylen)(*arr)
    dst_len = ctypes.c_size_t(0)

    _arr_move_first_occurrance(None, dst_len, src, src_len)
    if (dst_len.value != 0):
        dst = (ctypes.c_int * dst_len.value)()
        _arr_move_first_occurrance(dst, dst_len, src, src_len)
        return list(dst)
    return []

def test_arr_fill_with_fib():
    assert(arr_fill_with_fib(1) == [1])
    assert(arr_fill_with_fib(2) == [1, 1])
    assert(arr_fill_with_fib(3) == [1, 1, 2])
    assert(arr_fill_with_fib(5) == [1, 1, 2, 3, 5])

def test_arr_move_first_occurrance():
    assert(arr_move_first_occurrance([1]) == [1])
    assert(arr_move_first_occurrance([1, 1]) == [1])
    assert(arr_move_first_occurrance([1, 2, 3, 4]) == [1, 2, 3, 4])
    assert(arr_move_first_occurrance([1, 2, 2, 3]) == [1, 2, 3])
    
