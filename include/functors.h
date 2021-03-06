// compares two pointers by comparing objects they point to
template <typename T>
struct ValueComparer {
    bool operator() ( const T *lhs, const T *rhs) {
        // return (*lhs) < (*rhs);
        return lhs->operator<(*rhs);
    }
};
