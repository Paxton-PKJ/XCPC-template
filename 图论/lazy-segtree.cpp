/**
 * Author: Yuhao Yao
 * Date: 23-02-06
 * Description: Segment tree with lazy propogation.
 * Usage: Always define global apply functions (for both Info and Tag) to tell segment tree how you apply modification.
 *  Combine is set as plus so if you just let T be numerical type then you have range sum in the info and as range query
 * result. To have something different, say rangeMin, define a struct with constructer and + operation. Define in
 * Global: infoapply(\&info, l, r, Tag), tagApply(\&tag, l, r, val) Time: O(\log N) per operation. Status: tested on
 * https://www.luogu.com.cn/problem/P3384
 */
template <class Info, class Tag> class segTree
// 定义一个模板类segTree，它有两个类型参数Info和Tag，分别表示区间信息和标记信息
{
#define ls i << 1
#define rs i << 1 | 1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
    // 定义一些宏，用于简化代码中的表达式，比如左右子节点的编号、区间的中点、左右子区间等

    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    // 定义三个私有成员变量，n表示数列的长度，info和tag分别表示区间信息和标记信息的向量

  public:
    segTree(const std::vector<Info> &init) : n(init.size())
    // 定义一个构造函数，接受一个Info类型的向量作为初始值，并用它来初始化n
    {
        assert(n > 0);
        // 断言n大于0，否则抛出异常
        info.resize(4 << std::__lg(n));
        tag.resize(4 << std::__lg(n));
        // 将info和tag的大小调整为4倍于n的最小2的幂次，这是为了保证完全二叉树的结构
        auto build = [&](auto dfs, int i, int l, int r) {
            // 定义一个lambda表达式build，用于递归地构建完全二叉树
            // build接受四个参数，dfs表示自身的引用，i表示当前节点的编号，l和r表示当前节点对应的区间范围
            if (l == r)
            // 如果l等于r，说明当前节点是一个叶子节点
            {
                info[i] = init[l];
                // 将当前节点的区间信息设为初始值中对应位置的值
                return;
                // 返回递归
            }
            dfs(dfs, lson);
            dfs(dfs, rson);
            // 否则，递归地构建左右子节点
            pull(i);
            // 调用pull函数来更新当前节点的区间信息
        };
        build(build, 1, 0, n - 1);
        // 调用build函数来从根节点开始构建完全二叉树
    }

  private:
    void pull(int i)
    // 定义一个私有成员函数pull，用于更新某个节点的区间信息
    {
        info[i] = info[ls] + info[rs];
        // 将当前节点的区间信息设为左右子节点的区间信息之和（这里假设+是Info类型支持的操作）
    }

    template <class... T> void apply(int i, int l, int r, const T &...val)
    // 定义一个模板函数apply，用于将某个标记应用到某个节点上，并更新其区间信息
    // apply接受可变数量的参数，其中i表示当前节点的编号，l和r表示当前节点对应的区间范围，val表示要应用的标记值（可以是多个）
    {
        ::infoApply(info[i], l, r, val...);
        ::tagApply(tag[i], l, r, val...);
        // 调用全局函数infoApply和tagApply来分别更新当前节点的区间信息和标记信息（这里假设这两个函数已经定义好了）
    }

    void push(int i, int l, int r)
    // 定义一个私有成员函数push，用于将某个节点上的标记下传给其左右子节点，并清空其标记信息
    {
        if (tag[i] == Tag{})
            // 如果当前节点没有标记信息（假设Tag类型支持==操作符，并且Tag{}表示空标记）
            return;
        // 则直接返回
        apply(lson, tag[i]);
        apply(rson, tag[i]);
        // 否则，将当前节点上的标记应用到其左右子节点上
        tag[i] = {};
        // 然后将当前节点上的标记清空（假设Tag类型支持赋值操作符）
    }

  public:
    template <class... T> void rangeApply(int ql, int qr, const T &...val)
    // 定义一个模板函数rangeApply，用于将某个标记应用到数列中某个区间上，并更新相关节点的区间信息和标记信息
    // rangeApply接受可变数量的参数，其中ql和qr表示要操作的数列区间范围（半开半闭），val表示要应用的标记值（可以是多个）
    {
        auto dfs = [&](auto dfs, int i, int l, int r) {
            // 定义一个lambda表达式dfs，用于递归地处理每个节点
            // dfs接受四个参数，dfs表示自身的引用，i表示当前节点的编号，l和r表示当前节点对应的区间范围
            if (qr < l || r < ql)
                // 如果当前节点对应的区间与要操作的数列区间没有交集
                return;
            // 则直接返回递归
            if (ql <= l && r <= qr)
            // 如果当前节点对应的区间完全包含在要操作的数列区间内
            {
                apply(i, l, r, val...);
                // 则将要应用的标记应用到当前节点上，并更新其区间信息和标记信息
                return;
                // 返回递归
            }
            push(i, l, r);
            // 否则，如果当前节点对应的区间与要操作的数列区间有部分交集，则先将当前节点上的标记下传给其左右子节点，并清空其标记信息
            dfs(dfs, lson);
            dfs(dfs, rson);
            // 然后递归地处理左右子节点
            pull(i);
            // 最后更新当前节点的区间信息
        };
        dfs(dfs, 1, 0, n - 1);
        // 调用dfs函数来从根节点开始处理每个节点
    }

    Info rangeAsk(int ql, int qr)
    // 定义一个成员函数rangeAsk，用于获取数列中某个区间上累积操作结果（比如最小值、最大值、和等）
    {
        Info res{};
        // 定义一个Info类型变量res，并初始化为默认值（假设Info类型支持默认构造函数）
        auto dfs = [&](auto dfs, int i, int l, int r) {
            // 定义一个lambda表达式dfs，用于递归地处理每个节点并累积结果到res中
            // dfs接受四个参数，dfs表示自身引用，i表示当前节点编号，l和r表示当前节点对应区间范围
            if (qr < l || r < ql)
                // 如果当前节点对应区间与要查询数列区间没有交集，则直接返回递归。
                return;
            if (ql <= l && r <= qr)
            // 如果当前节点对应区间完全包含在要查询数列区间内，则将其区间信息累积到res中（假设+是Info类型支持操作）。
            {
                res = res + info[i];
                return;
            }
            push(i, l, r);
            // 否则如果当前节点对应区间与要查询数列区间有部分交集，则先将其标记下传给左右子节点，并清空其标记。
            dfs(dfs, lson);
            dfs(dfs, rson);
        };
        dfs(dfs, 1, 0, n - 1);
        return res;
    }

#undef rson
#undef lson
#undef mid
#undef rs
#undef ls
};