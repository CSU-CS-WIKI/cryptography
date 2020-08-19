# 计分标准

1. 古典密码学（总分30分）
   1. 必做（20分）
      1. 移位密码解密
      2. 仿射密码揭秘
      3. 列换位密码解密
   2. 二选一（10分）
      1. 维吉尼亚密码解密
      2. Many-Time-Pad攻击
2. 现代密码学（总分30分）
   1. 必做（25分）
      1. 因数分解攻击
      2. 选择密文攻击
      3. 共用模数攻击
   2. 二选一（5分）
      1. 阅读论文，利用中国剩余定理加速RSA失败时进行因数分解
      2. 阅读论文，进行低加密指数广播攻击
3. 安全协议（40分）
   1. 密钥协商协议（最高得分35分）

      完成对DH的中间人攻击
      1. 完成攻击并获取flag（30分）
      2. 自动化攻击过程（5分）
   2. 设计并完成一个数字签名软件（可以使用现有库）（总共40分，根据完成度给分）
      1. 可以创建、读取密钥文件
      2. 使用密钥对文件进行签名、校验
      3. 拥有密钥管理功能
   3. 门限方案
      1. 对给定的分享进行解密（10分）
      2. 设计一个能将定长的秘密进行创建，并且支持解密（15分）
      3. 支持两种门限方案（10分）
      4. 附加分值，自己添加额外功能（5分）示例：
         1. 添加对其他门限方案的支持
         2. 制作GUI方便使用

# 实验一 古典密码学

## 实验目的

本实验针对《现代密码学》课程中古典密码学进行的实验，锻炼学生对古典密码学算法的理解、密钥空间大小的认识、编码实现方面的能力。

提示：阅读代码未必会对解密有帮助，代码仅是对题目所述算法的实现。

## 实验内容

### 必做任务一 移位密码解密

移位密码是一类经典的古典密码，凯撒密码就是移位值为13的移位密码。

已知程序：

```c
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include<string.h>

char origin[512], casear[512], input[512];

int main()
{
	srand(time(NULL));
	int offset = rand() % 51 % 26;
	if(!offset) ++offset;
	FILE *book = fopen("Book1.txt", "r");
	int begin = rand() % (704871 - 1000);
	fseek(book, begin, SEEK_SET);
	char temp;
	while((temp=fgetc(book)) != '.');
	fgetc(book);
	for(int i = 0; i < 511; ++i){
		origin[i] = fgetc(book);
	}
	for(int i = 0; i < 511; ++i){
		if(isupper(origin[i])){
			casear[i] = (origin[i] - 'A' + offset) % 26 + 'A';
		}else if(islower(origin[i])){
			casear[i] = (origin[i] - 'a' + offset) % 26 + 'a';
		}else{
			casear[i] = origin[i];
		}
	}
	puts(casear);
	for(int i = 0; i < 511; ++i){
		input[i] = getchar();
	}
	int result = memcmp(origin, input, 512);
	if(!result){
		printf("Congratulation!");
	}else{
		printf("FAILED...");
	}
	return 0;
}
```

连接服务器后达到Congratulation的效果

截图，书写实验报告，回答课后问题。

#### 参考资料

- [Cryptanalysis of the Caesar Cipher](http://practicalcryptography.com/cryptanalysis/stochastic-searching/cryptanalysis-caesar-cipher/)

### 必做任务二 仿射密码解密

仿射密码也是一类经典的古典密码，通常加密方式为$c=m*a+b\mod n$，解密则使用$m=(c-b)*a^{-1}\mod n$，移位密码可以看做a=1的仿射密码。

```c
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include<string.h>

char origin[512], affine[512], input[512];
int map[128];
char txt[] = "abcdefghijklmnopqrstuvwxyz .,"; 

static inline int inmap(char c){
	return islower(c)||c == '.'||
		c == ' '|| c == ',';
}

int main()
{
	for(int i = 0; i < 29; ++i){
		map[txt[i]] = i + 1;
	}
	srand(time(NULL));
	int a = rand() % 29;
	while(a == 1) a = rand() % 29;
	int b = rand() % 29;
	FILE *book = fopen("Book1.txt", "r");
	int begin = rand() % (704871 - 1000);
	fseek(book, begin, SEEK_SET);
	char temp;
	while((temp=fgetc(book)) != '.');
	fgetc(book);
	for(int i = 0; i < 511; ++i){
		origin[i] = fgetc(book);
		if(isupper(origin[i])) origin[i] += 'a' - 'A';
	}
	for(int i = 0; i < 511; ++i){
		if(inmap(origin[i])){
			affine[i] = txt[(map[origin[i]] * a + b) % 29];
		}else{
			affine[i] = origin[i];
		}
	}
	puts(affine);
	for(int i = 0; i < 511; ++i){
		input[i] = getchar();
	}
	int result = memcmp(origin, input, 512);
	if(!result){
		printf("Congratulation!");
	}else{
		printf("FAILED...");
	}
	return 0;
}
```

连接服务器后达到Congratulation的效果

截图，书写实验报告，回答课后问题。

#### 参考资料

- [Cryptanalysis of the Affine Cipher](http://practicalcryptography.com/cryptanalysis/stochastic-searching/cryptanalysis-affine-cipher/)

### 必做任务三 列移位密码解密

阅读下面代码

```c
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include<string.h>

char origin[533], row[533], input[533];

int main()
{
	srand(time(NULL));
    int len = 512, count = 0;
	int r = rand() % 13;
	while(r == 1) r = rand() % 13;
    while(len % r) ++len;
	FILE *book = fopen("Book3.txt", "r");
	int begin = rand() % (704871 - 1000);
	fseek(book, begin, SEEK_SET);
	char temp;
	while((temp=fgetc(book)) != '.');
	fgetc(book);
	for(int i = 0; i < len; ++i){
		origin[i] = fgetc(book);
	}
	for(int i = 0; i < r; ++i){
		for(int j = i; j < len; j += r){
            row[count] = origin[j];
            ++count;
        }
	}
	puts(row);
	for(int i = 0; i < len; ++i){
		input[i] = getchar();
	}
	int result = memcmp(origin, input, len);
	if(!result){
		printf("Congratulation!");
	}else{
		printf("FAILED...");
	}
	return 0;
}
```

连接服务器后达到Congratulation的效果

截图，书写实验报告，回答课后问题。

#### 参考资料

- [Cryptanalysis of the Columnar Transposition Cipher](http://practicalcryptography.com/cryptanalysis/stochastic-searching/cryptanalysis-columnar-transposition-cipher/)

### 选做任务一 Crack the Vigenere Cipher

阅读Python代码

```python
import hashlib
import time
import random

key_len = random.randint(2, 13)


def gen_key_from_hex(hex_num):
    global key_len
    num = int(hex_num, 16)
    a = []
    while key_len > 0:
        a.append(num % 26)
        num //= 26
        key_len -= 1
    return a


text = open("Book4.txt", "r").read()
print(time.time())
key = gen_key_from_hex(hashlib.sha3_256(str(time.time()).encode()).hexdigest())

offset = random.randint(0, len(text) - 2000)
text = text[: 1024]
cipher = ""

for i in range(0, 1024):
    if ord('a') <= ord(text[i]) <= ord('z'):
        cipher += chr((ord(text[i]) - ord('a') + key[i % key_len]) % 26 + ord('a'))
    elif ord('A') <= ord(text[i]) <= ord('Z'):
        cipher += chr((ord(text[i]) - ord('a') + key[i % key_len]) % 26 + ord('Z'))
    else:
        cipher += text[i]

print(cipher)
key_str = ""
for i in key:
    key_str += chr(ord('a') + i)

answer = input()
while answer != "":
    if answer == key_str:
        print("Congratulations!")
        exit(0)
    else:
        print("FAILED...")
        answer = input()
```

连接服务器后达到Congratulation的效果

截图，书写实验报告，回答课后问题。

#### 参考资料

- [Cryptanalysis of the Vigenere Cipher](http://practicalcryptography.com/cryptanalysis/stochastic-searching/cryptanalysis-vigenere-cipher/)
- [Cryptanalysis of the Vigenere Cipher, Part 2](http://practicalcryptography.com/cryptanalysis/stochastic-searching/cryptanalysis-vigenere-cipher-part-2/)

### 选做任务二 Crack the Many-Time-Pad

**为了降低难度，OPT的范围是ASCII码范围，但是所有明文以及密钥都是可见ASCII码字符**

连接服务器，输入自己姓名对应的拼音，并输入根据获取的密文组解密出的密钥直至达到Congratulation的效果

#### 参考资料

- https://crypto.stackexchange.com/questions/33673/many-time-pad-attack-xor

## 问题讨论

1. 任务一中的加密算法的密钥空间为多少？
2. 任务二中的加密算法的密钥空间为多少？
3. 对于一个长度为$n$、不进行填充的明文来说，列换位密码的密钥空间是多少？
4. 简答题，根据所选的任务进行回答：
   1. 简单描述攻击维吉尼亚密码的方式
   2. 如果将OPT的加密范围变成字母形式（也就是说，明文、密文、密钥都只有英文字母），解密变简单了还是变复杂了？如果你需要对该种OPT进行攻击，简述攻击过程（或许你可以到[Text Characterisation](http://practicalcryptography.com/cryptanalysis/text-characterisation/)找点灵感）

## 实验环境

实验的环境为服务器开放的端口，连接方式不限。

可选方式举例：socket编程（硬核型）、netcat、pwntools、powercat

# 实验二 现代密码学

## 实验目的

本实验针对《现代密码学》课程中现代密码学进行的实验，锻炼学生对现代密码学算法的理解、一些常见攻击方式的理解以及编码能力。

## 实验内容

### 必做任务一 因数分解攻击

RSA的安全性依附于质因数分解的难度，若是密钥选用的整数不当，便可能遭受因数分解攻击。

连接服务器，服务器依次给出$n、e、c$，请还原m并输入服务器以达到Congratulation的效果。

### 必做任务二 选择密文攻击

密码学中，形容词“教科书般的\(textbook\)”并非是一个褒义词。

教科书般的RSA是易受选择密文攻击的。

现给出这样一个服务器，首先它会读入你的姓名来产生一个随机的明文，并给出$n、e、c$，随后同学可以进行两种输入：

1. 输入`-d [数字]`，如`-d 233`，该操作会获得对该密文进行解密以后的明文，注意该操作并不会解密原始的密文
2. 输入`-s [数字]`，如`-s 233`，该操作读入的数字若是原始明文，会给出Congratulation，否则给出FAILED。

连接服务器并达到Congratulation的效果。

#### 参考资料

- [How does a chosen plaintext attack on RSA work?](https://crypto.stackexchange.com/questions/2323/how-does-a-chosen-plaintext-attack-on-rsa-work)

### 必做任务三 共用模数攻击

对于同一条消息，如果使用相同的$n$不同的$e$加密，情况反而更危险。这一次就需要你完成对这样的RSA实现的攻击。

连接服务器并达到Congratulation的效果。

#### 参考资料

- [how to use common modulus attack?](https://crypto.stackexchange.com/questions/16283/how-to-use-common-modulus-attack)

### 选做任务一 Factoring RSA With CRT Optimization

When using RSA to perform a sign or decrypt operation, a common performance speedup is to use the Chinese Remainder Theorem to operate in the groups$Z/pZ$ and$ Z/qZ$, rather than $Z/nZ$ (where$ p∗q=n$). Rather than computing $x^d \mod n$ the optimization is outlined below: 

$$Compute:dp = e^{-1}\mod (p-1),dq = e^{-1}\mod (q-1),qinv=q^{-1}\mod p$$

The RSA private key is now the tuple $(p,q,dp,dq,qinv)$ rather than the usual value of just $d$. Now, to compute a signature $y$ for message$x$, or perform a decrypt operation on $x$ we do the following: 

$$y_1=x^{dp}\mod p,y_2=x^{dq}\mod q,h=qinv*(y_1-y_2)\mod p$$

$$y=y_2+h*q$$

As recently highlighted in [this paper](https://people.redhat.com/~fweimer/rsa-crt-leaks.pdf), if the computation of $ y1$ or $ y2$ (but not both) fails, it is possible to recover a factor of $n$.

Now, hers's your challenge, connect the server and give your answer.

### 选做任务二 广播攻击

教科书版的RSA除了会遭受选择密文攻击，也可能受到广播攻击。

广播攻击发生在加密使用的$e、m$相同，而$n$不同的时候。

连接服务器并给出正确的$m$通过实验。

#### 参考资料

- [Håstad's broadcast attack](https://en.wikipedia.org/wiki/Coppersmith%27s_attack#H%C3%A5stad's_broadcast_attack)

- [Hastad's Broadcast Attack - Cryptography | Coursera](https://www.coursera.org/lecture/number-theory-cryptography/hastads-broadcast-attack-fyPIB)<-这是个视频哟

## 问题讨论

1. 查阅资料回答，目前质因数分解的记录是多少位？
2. 查阅资料，分析至少一种是用在RSA中的填充方案。（如果没有头绪就去看看openssl使用RSA的方式吧）
3. 使用数学语言描述选择密文攻击与公用模数攻击。
4. 两个选做任务都有涉及中国剩余定理，请查阅资料，举一些中国剩余定理在密码学中的应用。可从算法设计、算法优化、算法攻击等方向入手。

## 实验环境

实验的环境为服务器开放的端口，连接方式不限。

可选方式举例：socket编程（硬核型）、netcat、pwntools、powercat

# 实验三 安全协议

## 实验目的

本实验针对《现代密码学》课程中现代密码学进行的实验，锻炼学生对现代密码学中协议的理解、一些常见攻击方式的理解以及编码能力。

## 实验内容

==注意，因为任务一不管从挑战性还是工作量来说都比另外两个任务小，故选做该任务的需要从实验目标中有自己思考做出创新才可获得满分。==

==但这并不意味着另外两个任务容易拿满分。==

### 选做任务一 密钥协商协议

Diffie-Hellman是一类经典的密钥协商协议，但是教科书版的DH协议中因为缺少认证的关系，易受到中间人攻击。

这次你充当的是一个截断了Alice与Bob通信链路的中间人，已知他们每次通话都会先通过DH协商密钥后，将协商好的密钥作为此次对话的密钥，之后的通信全部使用该密钥进行AES加密。

连接上服务器，并获取他们通信中的秘密。



### 选做任务二 数字签名协议

数字签名给数字世界提供了信用，是目前数字世界的基础协议之一。

你需要完成一个数字签名工具，需要具备以下功能：

1. 可以使用私钥进行签名，公钥进行验证。
2. 支持对文件进行签名、校验。
3. 拥有密钥管理功能。

可以使用现有数学、hash函数库，可以兼容、参考openssl但是不能使用openssl库。

### 选做任务三 秘密分享协议

秘密分享协议中有一类很经典的实现，称为门限方案。你的任务是：

1. 连接服务器，在给出分享后进行解密，服务器使用bloom门限方案。
2. 设计实现一个使用门限方案的秘密分享软件。
3. 为软件添加多种门限方案支持。

### 选做任务四 S/key协议



## 问题讨论

根据所选题目回答问题：

1. 查阅资料，简单描述目前的通信中减缓中间人攻击的措施。（譬如openssl中）
2. 查阅资料，简述三款你电脑上使用到了数字签名的软件，它们是在什么时候使用的？怎么用的？你能找到一些针对它们的攻击吗？
3. 查阅资料，简述秘密分享协议在实际网络安全中的应用。

## 实验环境

实验选做任务一的环境为服务器开放的端口，连接方式不限。

可选方式举例：socket编程（硬核型）、netcat、pwntools、powercat

编程任务的平台、语言不限，但需要在实验报告中增加一个环境说明部分，包括操作系统、编译器/解释器版本。

# 实验报告说明

实验报告格式：

1. 封面



2. 内容
   1. 每个必做任务与选做任务的攻击方式简述、攻击成功截图、关键代码、程序运行界面（CLI/GUI均可）
   2. 回答问题