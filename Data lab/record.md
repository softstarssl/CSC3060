# record

## bitXor
这个比较简单了，没什么好说的
~~~cpp
int bitXor(int x, int y) 
{
  return (~(x & y) & ~(~x & ~y));
}
~~~

## tmin
补码的数值计算式：$-2^{31}·b_{31} + \sum_{i = 0}^{30} 2^i · b_i$

所以当补码的最高位是1,后面的全都是0，可以得到补码表示法能表示的最小值 $-2^{31}$
其补码就是 (1 << 31)
~~~cpp
int tmin(void) 
{
  //Tmin = 1000...0000
  return 1 << 31;

}
~~~

## isTmax
判断传入的数是不是最大数: 01111....111

具体的写到代码里面了
~~~cpp
int isTmax(int x) 
{
  //Tmax 的性质-> ~x = x + 1
  //注意到 -1 同样也有这个性质
  //所以判断 !(x + 1) 来排除 -1 的情况
  int y = x + 1;
  return !((~x ^ y) | (!y));
}
~~~

## allOddBits
判断当前数字其奇数上面是否为全部为1，特别注意最低位是第0位

注意到 $A_{(16)} = 10_{(10)} = 1010_{(2)},AA = 1010101_{(2)}$,一个十六进制字符占据着四个二进制字节,以此我们扩展到32位，就是 $AAAAAAAA_{(16)}$ 就是我们要找的一个标准数字$\text{mask}$，然后我们用传入这个数与mask做 & 运算，看看是否与mask 相等
~~~cpp
int allOddBits(int x) 
{
  int mask = 0xAA | (0xAA << 8);
  mask = mask | (mask << 16);
  return !(mask ^ (mask & x));
}
~~~
## negate
最经典的求解负数，经典公式
~~~cpp
int negate(int x) 
{
  return ~x + 1;
}
~~~

## isAsciiDigit
判断这个字符是不是满足 $0x30\leq x \leq 0x39$

其实就是判断 x - 0x30和0x39 - x 是不是负数罢了，x - 0x30 = x + (-0x30) = x + (~0x30 + 1)
~~~cpp
int isAsciiDigit(int x) 
{
  int tmin = 1 << 31;
  int inf = x + (~0x30 + 1); //x - 0x30
  int sup = 0x39 + (~x + 1); //0x39 - x
  //检查符号位是否为0
  return !((inf & tmin) | (sup & tmin));
}
~~~

## conditional
返回条件语句 x?y:z;

首先将 x 变为最好分析的 0000000... 和 1....，使用 x = !x，则 x = 0 时将 x 转化为 1 ，反之将 x 转化为0，然后 x = -x (~x + 1)，就能将 0 转化成0000000...，1转化成111111...，（特别注意这里的0/1和最开始是相反的！！！所以后面似 y & ~x 而不是 y & x）然后 y & ~x | z & x来判断该返回哪个
~~~cpp
int conditional(int x, int y, int z) 
{
  x = !x; //x为0时变为1，x非0时变为0
  x = ~x + 1; //x为0时变为0x00000000，x非0时变为0xFFFFFFFF
  return (y & ~x) | (z & x);
}
~~~