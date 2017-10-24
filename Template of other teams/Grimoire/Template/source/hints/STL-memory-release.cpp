template <typename T>
__inline void clear(T& container) {
	container.clear(); // 或者删除了一堆元素
	T(container).swap(container);
}
