/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif

/*
写在最前面，一般这个作业不允许我们直接显式的使用超过0xFF(255)的常数，
所以我们需通过位运算来构造更大的常数
*/

//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) 
{
  return (~(x & y) & ~(~x & ~y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) 
{
  //Tmin = 1000...0000
  return 1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) 
{
  //Tmax 的性质-> ~x = x + 1
  //注意到 -1 同样也有这个性质
  //所以判断 !(x + 1) 来排除 -1 的情况
  int y = x + 1;
  return !((~x ^ y) | (!y));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
//注意最低位是从0开始编号的
int allOddBits(int x) 
{
  int mask = 0xAA | (0xAA << 8);
  mask = mask | (mask << 16);
  return !(mask ^ (mask & x));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) 
{
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) 
{
  int tmin = 1 << 31;
  int inf = x + (~0x30 + 1); //x - 0x30
  int sup = 0x39 + (~x + 1); //0x39 - x
  //检查符号位是否为0
  return !((inf & tmin) | (sup & tmin));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
/*核心思路：将 x 转化为全0或全1的掩码，
然后与 y 和 z 进行与运算，最后或运算得到结果*/
int conditional(int x, int y, int z) 
{
  x = !x; //x为0时变为1，x非0时变为0
  x = ~x + 1; //x为0时变为0x00000000，x非0时变为0xFFFFFFFF
  return (y & ~x) | (z & x);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) 
{
  int diff = y + (~x + 1); //y - x
  int tagx = (x >> 31) & 1; //x的符号位
  int tagy = (y >> 31) & 1; //y的符号位
  int tagdiff = (diff >> 31) & 1; //y - x 的符号位
  //x和y符号位相同，则看y - x 的符号位
  //x和y符号位不同，则看x的符号位
  return (tagx & !tagy) | (!(tagx ^ tagy) & !tagdiff);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) 
{
  return( (x|(~x + 1)) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
/*有点不太像人类了，手动模拟二分/倍增法都出来了
  没有循环语句的的坏处来了
*/
int howManyBits(int x) 
{
  //首先我们要统一处理正数，所以先把负数转化成正数，其实就是取反,这样方便消去符号位
  int tag = x >> 31;
  int bit_0,bit_1,bit_2,bit_4,bit_8,bit_16;
  //tag = 0000...0 = 0 ,当 x 非负, tag = 111...1111 = -1,x 是负数
  x = x ^ tag; // tag = 0,x^tag = x; tag = -1, x^tag = ~x
  
  //然后就是伟大的倍增法
  
  bit_16 = !(!(x >> 16)) << 4; //是否高16位有1
  x = x >> bit_16; //接下来以此类推
  bit_8 = !(!(x >> 8)) << 3;
  x = x >> bit_8;
  bit_4 = !(!(x >> 4)) << 2;
  x = x >> bit_4;
  bit_2 = !(!(x >> 2)) << 1;
  x = x >> bit_2;
  bit_1 = !(!(x >> 1));
  x = x >> bit_1;
  bit_0 = x;
  return bit_0 + bit_1 + bit_2 + bit_4 + bit_8 + bit_16 + 1; 
  //最后加1是因为符号位
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
//传入的这个无符号整数表示一个单精度浮点数，有三个部分：
// 1位符号位，8位指数位，23位尾数位
unsigned floatScale2(unsigned uf) 
{
  int sign = uf >> 31; //符号位
  int exp = (uf >> 23) & ((1 << 8) - 1); //指数位
  int frac = uf & ((1 << 23) - 1); //尾数位
  //判断 是否为NaN或无穷大，NaN前面说了返回自身，无穷大的两倍还是无穷大，也返回自身
  if(exp == 0xFF) return uf; 
  //判断是否为非规格化数
  if(exp == 0)
  {
    frac = frac << 1; //尾数左移一位
    if(frac & (1 << 23)) //判断是否变为规格化数
    {
      exp = 1; //变为规格化数，指数变为1
      frac = frac & ((1 << 23) - 1); //去掉隐含的1
    }
    return (sign << 31) | (exp << 23) | frac;
  }
  //规格化数，指数加1
  exp = exp + 1;
  //判断是否变为无穷大
  if(exp == 0xFF) return (sign << 31) | (exp << 23); //尾数为0
  return (sign << 31) | (exp << 23) | frac;

}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) 
{
  int sign = uf >> 31; //符号位
  int exp = (uf >> 23) & ((1 << 8) - 1); //指数位
  int frac = uf & ((1 << 23) - 1); //尾数位
  int E = exp - 127; //实际指数
  int ans;

  if(exp == 0xFF) return 0x80000000u; //NaN或无穷大
  if(E < 0) return 0; //小于1的数，转化为整数为0
  if(E >= 31) return 0x80000000u; //超出 int 范围

  ans = frac | (1 << 23); //加上隐含的1,把 frac 按照正数数值来算

  if(E >= 23) ans = ans << (E - 23); //乘的> 2^23 ，相当于还要左移
  else ans = ans >> (23 - E); //乘的< 2^23 ，相当于右移

  return sign ? -ans : ans; //根据符号位返回正负值
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) 
{
    int INF = 0xFF << 23; //表示无穷大的浮点数
    int exp = x + 127; //计算指数位
    if(x < -149) return 0; //太小，返回0
    if(exp <= 0) return 1 << (exp + 22); //非规格化数
    if(exp >= 255) return INF; //太大

    return exp << 23; //返回浮点数表示
}
