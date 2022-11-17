#ifdef LOCAL
template<typename T1, typename T2>
ostream& operator<<(ostream& os, pair<T1, T2> p) {
	return os << '(' << p.first << ' ' << p.second << ')';
}
template<typename T, size_t N> struct tuplePrinter {
	static ostream& print(ostream& os, T t) { return tuplePrinter<T, N - 1>::print(os, t) << ' ' << get<N - 1>(t); }
};
template<typename T> struct tuplePrinter<T, 1> {
	static ostream& print(ostream& os, T t) { return os << get<0>(t); }
};
template<typename ...args> ostream& print_tuple(ostream& os, tuple<args...> t) {
	return tuplePrinter<decltype(t), sizeof...(args)>::print(os << '(', t) << ')';
}
template<typename ...args> ostream& operator<<(ostream& os, const tuple<args...> t) {
	return print_tuple(os, t);
}
template<typename T1, typename T2, typename T3>
ostream& operator<<(ostream& os, priority_queue<T1, T2, T3> v) {
	bool flag = false;
	os << '[';
	while (sz(v)) {
		if (flag) {
			os << ' ';
		}
		flag = true;
		os << v.top();
		v.pop();
	}
	os << ']';
	return os;
}
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream& os, C container) {
	bool flag = false;
	os << '[';
	for (auto x : container) {
		if (flag) {
			os << ' ';
		}
		flag = true;
		os << x;
	}
	return os << ']';
}
void debug_out() { cerr << endl; }
template<typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
	cerr << H;
	if (sizeof...(T)) {
		cerr << ", ";
	}
	debug_out(T...);
}
#define debug(...) cerr << #__VA_ARGS__ << " = ", debug_out(__VA_ARGS__)
#else
#define debug(...) 0xF
#endif
