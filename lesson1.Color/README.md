# 第1章：颜色

>任何事物的颜色可以通过三基色（红red、绿green、蓝blue）混合而成，颜色的分量（也有叫做通道）即指red、green、blue的所占比例，除了这三种分量外，我们有时候还需要使用到透明度分量（alpha）

-------------------

## 颜色的表示

### 使用3个float表示颜色

>考虑到运算性能和内存开销，使用3个float来表示其red、green、blue分量，一般使用范围为0到1，1为100%
``` c++
    struct Color3f
    {
        float   _red;
        float   _green;
        float   _blue;

    public:
        Color3f() {}
        Color3f(const Color3f& c):_red(c._red), _green(c._green), _blue(c._blue) {}
        Color3f(float r, float g, float b) : _red(r), _green(g), _blue(b) {}

        Color3f     operator +(const Color3f& c) const { return Color3f(_red + c._red, _green + c._green, _blue + c._blue); }
        Color3f     operator -(const Color3f& c) const { return Color3f(_red - c._red, _green - c._green, _blue - c._blue); }
        Color3f&    operator +=(const Color3f& c) { _red += c._red, _green += c._green, _blue += c._blue; return *this; }
        Color3f&    operator -=(const Color3f& c) { _red -= c._red, _green -= c._green, _blue -= c._blue; return *this; }
        Color3f     operator *(float k) const { return Color3f(_red * k, _green * k, _blue * k); }
        Color3f     operator /(float k) const { return Color3f(_red / k, _green / k, _blue / k); }
        Color3f&    operator *=(float k) { _red *= k, _green *= k, _blue *= k; return *this; }
        Color3f&    operator /=(float k) { _red /= k, _green /= k, _blue /= k; return *this; }
    };
```

### 使用4个float表示颜色

>使用4个float表示具有透明度的颜色，其中alpha，0表示全透明，1表示不透明
``` c++
    struct Color4f
    {
        float   _red;
        float   _green;
        float   _blue;
        float   _alpha;

    public:
        Color4f() {}
        Color4f(const Color3f &c) :_red(c._red), _green(c._green), _blue(c._blue), _alpha(1.0f) {}
        Color4f(float r, float g, float b, float a = 1.0f) : _red(r), _green(g), _blue(b), _alpha(a) {}

        Color4f     operator +(const Color4f& c) const { return Color4f(_red + c._red, _green + c._green, _blue + c._blue, _alpha + c._alpha); }
        Color4f     operator -(const Color4f& c) const { return Color4f(_red - c._red, _green - c._green, _blue - c._blue, _alpha - c._alpha); }
        Color4f&    operator +=(const Color4f& c) { _red += c._red, _green += c._green, _blue += c._blue, _alpha += c._alpha; return *this; }
        Color4f&    operator -=(const Color4f& c) { _red -= c._red, _green -= c._green, _blue -= c._blue, _alpha -= c._alpha; return *this; }
        Color4f     operator *(float k) const { return Color4f(_red * k, _green * k, _blue * k, _alpha * k); }
        Color4f     operator /(float k) const { return Color4f(_red / k, _green / k, _blue / k, _alpha / k); }
        Color4f&    operator *=(float k) { _red *= k, _green *= k, _blue *= k, _alpha *= k; return *this; }
        Color4f&    operator /=(float k) { _red /= k, _green /= k, _blue /= k, _alpha /= k; return *this; }
    };
```
### 使用4个字节表示颜色

>很多时候我们也采用4个字节表示颜色，由于每个字节的表示范围为0-255，可以理解为它将颜色的各分量分成了256个程度，那么除去透明度，它可以表示的颜色共256*256*256种，相比上一种表示方式，它的精度远不如上一种，但节省大量内存开销，事实上目前的显示设备大多也只支持这么多的颜色种数。
``` c++
    typedef unsigned char	byte;
	
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
        Color4b() {}
        Color4b(const Color4b& c) : _value(c._value) {}
        Color4b(int value) : _value(value) {}
        Color4b(byte a, byte r, byte g, byte b) : _alpha(a), _blue(b), _green(g), _red(r) {}
    };
```
- 这里我们使用了联合体定义Color4b结构，这样可以方便了各分量进行访问，也方便了int赋值（形如0xAABBGGRR）。
- 这里我们没有使用class来定义颜色，因为颜色本来就只是一种描述结构，与类的封装、继承、多态毫无关系，我们仅重载一些运算符方便计算表达。

-------------------

## 颜色的混合

### 不透明颜色和半透明颜色的混合

> 假设一不透明的背景图像是A，另一幅透明的图象是B，那么透过B去看A，看上去的图象C就是B和A的混合图象
> 
> C = (1 - B.alpha) * A + B.alpha * B
``` c++
Color3f sge::alphaBlend(const Color3f &bgcolor, const Color4f &fcolor)
{
    float pA = 1.0f - fcolor._alpha;
    Color3f out;
    out._red = pA * bgcolor._red + fcolor._alpha * fcolor._red;
    out._green = pA * bgcolor._green + fcolor._alpha * fcolor._green;
    out._blue = pA * bgcolor._blue + fcolor._alpha * fcolor._blue;
    return out;
}
```

### 半透明颜色和半透明颜色的混合

> 半透明玻璃A与半透明玻璃B重叠与单个半透明玻璃C的效果一样，我们可以根据A与B计算出C的颜色和透明度。
> 
> 可以想象一束光透过透明度为80%的玻璃后光线强度变为80%，再透过一个透明度为60%的玻璃后光线强度剩下48%，由于我们采用不透明度，我们将A、B、C透明度简写为A.a、B.a、C.a,则:
>> C.a = 1 - ((1 - A.a) * (1 - B.a)) = A.a + B.a - A.a * B.a
>
> 我们已经知道，在背景色上如何叠加半透明色，我们可以分为两步，先在背景色上叠上第一个半透明颜色A，然后在叠好的结果上叠上第二个半透明颜色B，设原始背景色为R1,第一次的叠好的结果为T1，全叠好的结果为T2
>> T1 = (1 - A.a) * R1 + A.a * A；
>> 
>> T2 = (1 - B.a) * T1 + B.a * B
>>>  = (1 - B.a) * ((1 - A.a) * R1 + A.a * A) + B.a * B
>>>  = (1 - B.a) * (1 - A.a) * R1 + (1 - B.a) * A.a * A + B.a * B
>
> 而T2还应等同于R1与C的直接混合结果
>> T2 = (1 - C.a) * R1 + C.a * C
>>>  = (1 - (A.a + B.a - A.a * B.a)) * R1 + (A.a + B.a - A.a * B.a) * C
>>>  = (1 - A.a) * (1 - B.a) * R1 + (A.a + B.a - A.a * B.a) * C
>
> 联立上述等式，同减(1 - A.a) * (1 - B.a) * R1,可以消除R1,化简得C:
>> C = [(1 - B.a) * A.a * A + B.a * B] / (A.a + B.a - A.a * B.a)
``` c++
Color4f sge::alphaBlend(const Color4f &c1, const Color4f &c2)
{
    Color4f out;
    out._alpha = c1._alpha + c2._alpha - c1._alpha * c2._alpha;
    float k = (1.0f - c2._alpha) * c1._alpha;
    out._red = (k * c1._red + c2._alpha * c2._red) / out._alpha;
    out._green = (k * c1._green + c2._alpha * c2._green) / out._alpha;
    out._blue = (k * c1._blue + c2._alpha * c2._blue) / out._alpha;
    return out;
}
```

-------------------

### 本节不能生成可执行程序

-------------------
### 本章代码位于sgeMath.h中，github链接https://github.com/xiangwencheng1994/sge/tree/master/lesson1.Color