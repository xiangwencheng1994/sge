# 第1章：颜色的表示

>任何事物的颜色可以通过三基色（红red、绿green、蓝blue）混合而成，颜色的分量（也有叫做通道）即指red、green、blue的所占比例，除了这三种分量外，我们有时候还需要使用到透明度分量（alpha）

-------------------

## 使用3个float表示颜色

>考虑到运算性能和内存开销，使用3个float来表示其red、green、blue分量，一般使用范围为0到1，1为100%
``` c++
    struct Color3f
    {
        float   _red;
        float   _green;
        float   _blue;

    public:
        Color3f() {}
        Color3f(float r, float g, float b) : _red(r), _green(g), _blue(b) {}
    };
```

## 使用4个float表示颜色

>使用4个float表示具有透明度的颜色，其中alpha，0表示不透明，1表示100%透明
``` c++
    struct Color4f
    {
        float   _red;
        float   _green;
        float   _blue;
        float   _alpha;

    public:
        Color4f() {}
        Color4f(Color3f &c):_red(c._red), _green(c._green), _blue(c._blue), _alpha(0) {}
        Color4f(float r, float g, float b, float a = 0) : _red(r), _green(g), _blue(b), _alpha(a) {}
    };
```
## 使用4个字节表示颜色
>很多时候我们也采用4个字节表示颜色，由于每个字节的表示范围为0-255，可以理解为它将颜色的各分量分成了256个程度，那么除去透明度，它可以表示的颜色共256*256*256种，相比上一种表示方式，它的精度远不如上一种，但节省大量内存开销，事实上目前的显示设备大多也只支持这么多的颜色种数。
``` c++
	typedef unsigned char       byte;
	
    union Color4b {
        int     _value;
        struct
        {
            byte    _alpha;
            byte    _blue;
            byte    _green;
            byte    _red;
        };

    public:
        Color4b(int value) : _value(value) {}
        Color4b(byte a, byte r, byte g, byte b) : _alpha(a), _blue(b), _green(g), _red(r) {}
    };
```
- 这里我们使用了联合体定义Color4b结构，这样可以方便了各分量进行访问，也方便了int赋值（形如0xAABBGGRR）。
- 这里我们没有使用class来定义颜色，因为颜色本来就只是一种描述结构，与类的封装、继承、多态毫无关系。

### 本章代码位于sgeMath.h中，github链接https://github.com/xiangwencheng1994/sge/tree/master/lesson1.Color