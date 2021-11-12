# Java专题基础

### 目录

---
<a href="#1">1. String 中的”+”操作是怎么回事?</a> <br>
<a href="#2">2. StringBuilder和StringBuffer 底层是怎么实现的。</a> <br>
<a href="#3">3. String 类中常用的方法。</a> <br>
<a href="#4">4. 创建虚引用的时候, 构造方法传入一个 ReferenceQueue, 作用是什么。</a> <br>
<a href="#5">5. 栈溢出的原因和解决方法。</a> <br>
<a href="#6">6. HashMap的加载因子的作用。</a> <br>
<a href="#7">7. HashMap中的 key 可以是任意对象吗?(Set 中元素的内容可以改变吗?)</a> <br>
<a href="#8">8. 如果你定义一个类,包括学号, 姓名, 分数, 如何把这个对象作为 key?</a> <br>
<a href="#9">9. Java是如何实现跨平台的。</a> <br>
<a href="#10">10. 什么是泛型,为什么要使用以及类型擦除。</a> <br>
<a href="#11">11. Java中的 NIO, BIO 分别是什么。NIO 主要用来解决什么问题。</a> <br>
<a href="#12">12. 面向对象的 6 个基本原则(设计模式的 6 个基本原则)。</a> <br>
<a href="#13">13. JDK 源码中用到的设计模式 。</a> <br>
<a href="#14">14. 执行 Student s = new Student();在内存中做了哪些事情?</a> <br>
<a href="#15">15. 你知道的开源软件有哪些?</a> <br>
<a href="#16">16. String 型变量如何转成 int 型变量,反过来呢?</a> <br>
<a href="#17">17. 怎么判断数组是 null 还是为空?</a> <br>
<a href="#18">18. 怎样让一个线程放弃锁。</a> <br>
<a href="#19">19. IO 里面常见的类。</a> <br>
<a href="#20">20. xml 解析方式。</a> <br>


### <a name="1">1. String中的”+”操作是怎么回事?</a>
1.String 中的”+”操作是怎么回事?

#### 情况 1:
1. String a = "ab";
2. String bb = "b";
3. String b = "a" + bb;
System.out.println((a == b));
“String+变量”因为编译时无法进行优化,所以这一条语句的操作是在运行时进行的,且
会产生新的对象,而不是直接从 jvm 的 string 池中获取。
java 中 String 的+运算符编译后其实是转换成了这样的代码: 
3. String b = new StringBuilder().append("a").append(bb).toString(); <br>
其中,StringBuilder 的 toString 方法,使用 new String(...);来构造一个 String 对象。 <br>
    
    public String toString() { // StringBuilder 的 toString 方法 <br>
        // Create a copy, don't share the array <br>
        return new String(value, 0, count); <br>
    }

#### 情况 2:
一个特殊的例子: <br>
    String str = “This is only a” + “ simple” + “ test”;//“+”连接的都是字符串常量 <br>
    StringBuffer builder = new StringBuilder(“This is only a”).append(“ simple”).append(“ test”); <br>
    你会很惊讶的发现,生成 str 对象的速度简直太快了,而这个时候 StringBuffer 居然速度上根本一点都不占优势。其实这是 JVM 的一个把戏,实际上: <br>
    String str = “This is only a” + “ simple” + “test”; <br>
    其实就是: <br>
    String str = “This is only a simple test”; <br>
    所以不需要太多的时间。但大家这里要注意的是,如果你的字符串是来自另外的String 对象的话,速度就没那么快了,譬如: <br>
    String str2 = “This is only a”; <br>
    String str3 = “ simple”; <br>
    String str4 = “ test”; <br>
    String str1 = str2 +str3 + str4; //“+”连接的是字符串变量 <br>
    这时候 JVM 会规规矩矩的按照原来的方式去做。 <br>


### <a name="2">2. StringBuilder和StringBuffer底层是怎么实现的。</a>
&ensp;&ensp;&ensp;&ensp;
    每个 StringBuffer 对象都有一定的缓冲区容量(可变长的字符数组,类似于
ArrayList 的底层实现),默认初始容量为 16 个字符。当字符串大小没有超过
容量时,不会分配新的容量;当字符串大小超过容量时,会自动扩容(扩容后
的容量大约是之前的 2 倍)。StringBuilder 和 StringBuffer,字符串都是存放在
char[]中的。


### <a name="3">3. String类中常用的方法。</a>
1. charAt(int index) :返回指定索引处的 char 值。
2. intern() :返回字符串对象的规范化表示形式。
3. isEmpty() :当且仅当 length() 为 0 时返回 true。
4. length() :返回此字符串的长度。
5. substring(int beginIndex) :返回一个新的字符串,它是此字符串的一个子字符串。  <br>
&ensp;&ensp;&ensp;&ensp;
    substring(int beginIndex, int endIndex) :返回一个新字符串,它是此字
符串的一个子字符串。
6. toLowerCase() :将此 String 中的所有字符都转换为小写。
toUpperCase():将此 String 中的所有字符都转换为大写。
7. trim():去除字符串首尾空格。
8. valueOf(Object obj) : 返回 Object 参数的字符串表示形式。
9. equals(Object anObject) :将此字符串与指定的对象比较。


### <a name="4">4. 创建虚引用的时候,构造方法传入一个 ReferenceQueue,作用是什么。</a>
&ensp;&ensp;&ensp;&ensp;
    虚引用必须和引用队列关联使用,当垃圾回收器准备回收一个对象时,如
果发现它还有虚引用,就会把这个虚引用加入到与之关联的引用队列中。程序
可以通过判断引用队列中是否已经加入了虚引用,来了解被引用的对象是否将
要被垃圾回收。如果程序发现某个虚引用已经被加入到引用队列,那么就可以
在所引用的对象的内存被回收之前采取必要的行动。


### <a name="5">5. 栈溢出的原因和解决方法。</a>
原因: <br>
(1)大量的递归调用,在不断的压栈过程中,造成栈容量超过而导致溢出。 <br>
(2)由于分配了过大的局部变量。 <br>
**解决方法:**
(1)用栈把递归转换成非递归。 <br>
(2)使用静态对象替代非静态局部对象。 <br>
&ensp;&ensp;&ensp;&ensp;
    在递归函数设计中,可以使用静态对象替代非静态局部对象(即栈对象),
这不仅可以减少每次递归调用和返回时产生和释放非静态对象的开销,而且静
态对象还可以保存递归调用的中间状态,并且可为各个调用层所访问。 <br>
(3)增加堆栈的大小 <br>


### <a name="6">6. HashMap的加载因子的作用。</a>
&ensp;&ensp;&ensp;&ensp;
    加载因子是表示 Hash 表中元素的填满程度。若加载因子越大,填满的元素
越多,好处是,空间利用率高了,但冲突的机会加大了,增加查询数据的时间
开销。反之,加载因子越小,填满的元素越少,好处是,冲突的机会减小了,
会提高数据查询的性能,但空间浪费多了。特别地,JDK1.8 中对 HashMap 进
行了增强,如果一个桶上的节点数量过多,链表+数组的结构就会转换为红黑树。


### <a name="7">7. HashMap中的 key 可以是任意对象吗?(Set 中元素的内容可以改变吗?)</a>
&ensp;&ensp;&ensp;&ensp;
    可变对象和不可变对象都可以。可变对象是指创建后自身状态能改变的对
象。换句话说,可变对象是该对象在创建后它的哈希值(由类的 hashCode()
方法可以得出哈希值)可能被改变。 <br>
&ensp;&ensp;&ensp;&ensp;
    如果可变对象在 HashMap 中被用作 key,当对象中的属性改变时,则对象
HashCode 也可能进行相应的改变,这将导致下次无法查找到已存在 Map 中的
数据;或者当想删除被改变对象的时候,由于找不到该对象,无法删除,会造
成内存泄漏。 所以当 hashCode( )重写的时候,最好不能依赖该类的易变属性,
这样就可以保证成员变量改变的时候,该对象的哈希值不变。

### <a name="8">8. 如果你定义一个类,包括学号,姓名,分数,如何把这个对象作为 key?</a>
&ensp;&ensp;&ensp;&ensp;
    需要重写 equals( )方法和 hashCode()方法,必须保证对象的属性改变
时,其 hashCode()返回值不能改变。

### <a name="9">9. Java是如何实现跨平台的。</a>
&ensp;&ensp;&ensp;&ensp;
    java 跨平台的实质是虚拟机的跨平台。JVM 也是一个软件,不同的平台有
不同的版本。我们编写的 Java 源码,编译后会生成一种 .class 文件,称为字
节码文件。Java 虚拟机就是负责将字节码文件翻译成特定平台下的机器码然后
运行。也就是说,只要在不同平台上安装对应的 JVM,就可以运行字节码文件,
运行我们编写的 Java 程序。
### <a name="10">10. 什么是泛型,为什么要使用以及类型擦除。</a>
&ensp;&ensp;&ensp;&ensp;
    泛型的本质就是“参数化类型”,也就是说所操作的数据类型被指定为一个参数。
创建集合时就指定集合元素的数据类型,该集合只能保存其指定类型的元素,
避免使用强制类型转换。 <br>
&ensp;&ensp;&ensp;&ensp;
    Java 编译器生成的字节码是不包含泛型信息的,泛型类型信息将在编译处理时
被擦除,这个过程即类型擦除。类型擦除可以简单的理解为将泛型 java 代码转
换为普通 java 代码,只不过编译器更直接点,将泛型 java 代码直接转换成普通
java 字节码。 <br>
类型擦除的主要过程如下: <br>
一.将所有的泛型参数用其最左边界(最顶级的父类型)类型替换。 <br>
二.移除所有的类型参数。 <br>

### <a name="11">11. Java中的 NIO,BIO 分别是什么。NIO 主要用来解决什么问题。</a>
NIO 的主要作用就是用来解决速度差异的。 <br>
Java 中 NIO 和 IO 之间的区别。 <br>
1. 面向流与面向缓冲 <br>
&ensp;&ensp;&ensp;&ensp;
    Java NIO 和 IO 之间第一个最大的区别是,IO 是面向流的,NIO 是面向缓
冲区的。 <br>
&ensp;&ensp;&ensp;&ensp;
    Java IO 面向流意味着每次从流中读一个或多个字节,直至读取所有字节,
它们没有被缓存在任何地方。此外,它不能前后移动流中的数据。在 Java NIO
中把数据读取到一个缓冲区中,需要时可在缓冲区中前后移动。这就增加了处
理过程中的灵活性。而且,需确保当更多的数据读入缓冲区时,不要覆盖缓冲
区里尚未处理的数据。
2. 阻塞与非阻塞 IO <br>
&ensp;&ensp;&ensp;&ensp;
    Java IO 的各种流是阻塞的。这意味着,当一个线程调用 read() 或 write()
时,该线程被阻塞,直到有一些数据被读取,或数据完全写入。该线程在此期
间不能再干任何事情了。Java NIO 的非阻塞模式,使一个线程从某通道发送请
求读取数据,但是它仅能得到目前可用的数据,如果目前没有数据可用时,就
什么都不会获取,而不是保持线程阻塞,所以直至数据变的可以读取之前,该
线程可以继续做其他的事情。非阻塞写也是如此。一个线程请求写入一些数据
到某通道,但不需要等待它完全写入,这个线程同时可以去做别的事情。 线程
通常将非阻塞 IO 的空闲时间用于在其它通道上执行 IO 操作,所以一个单独的
线程现在可以管理多个输入和输出通道(channel)。
3. 选择器(Selector) <br>
&ensp;&ensp;&ensp;&ensp;
    Java NIO 的选择器允许一个单独的线程来监视多个输入通道,你可以注册
多个通道使用一个选择器,然后使用一个单独的线程来“选择”通道:这些通道里
已经有可以处理的输入,或者选择已准备写入的通道。为了将 Channel 和
Selector 配合使用,必须将 channel 注册到 selector 上,通过
SelectableChannel.register()方法来实现。这种选择机制,使得一个单独的线程
很容易来管理多个通道。只要 Channel 向 Selector 注册了某种特定的事件,
Selector 就会监听这些事件是否会发生,一旦发生某个事件,便会通知对应的
Channel。使用选择器,借助单一线程,就可对数量庞大的活动 I/O 通道实施
监控和维护。 <br>
&ensp;&ensp;&ensp;&ensp;
    例如,在一个聊天服务器中。这是在一个单线程中使用一个 Selector 处理 3 个
Channel 的图示: <br>
![05_11_1](/data/images/Java应届生面试突击/Java基础/05_11_1.png) <br>

&ensp;&ensp;&ensp;&ensp;
    要使用 Selector,得向 Selector 注册 Channel,然后调用它的 select()方法。
这个方法会一直阻塞到某个注册的通道有事件就绪。一旦这个方法返回,线程
就可以处理这些事件,事件的例子有如新连接进来,数据接收等。反应器模式。
NIO 的原理。 <br>
在 NIO 中有几个核心对象:缓冲区(Buffer)、通道(Channel)、选择器(Selector)。 <br>
一. 缓冲区(Buffer) <br>
&ensp;&ensp;&ensp;&ensp;
    缓冲区实际上是一个容器对象,其实就是一个数组,在 NIO 库中,所有数
据都是用缓冲区处理的。在读取数据时,它是直接读到缓冲区中的;在写入数
据时,它也是写入到缓冲区中的;任何时候访问 NIO 中的数据,都是将它放到
缓冲区中。在 NIO 中,所有的缓冲区类型都继承于抽象类 Buffer,最常用的就
是 ByteBuffer。
而在面向流 I/O 系统中,所有数据都是直接写入或者直接将数据读取到
Stream 对象中。 <br>
![05_11_2](/data/images/Java应届生面试突击/Java基础/05_11_2.png) <br>

二. 通道(Channel) <br>
&ensp;&ensp;&ensp;&ensp;
    通道是一个对象,通过它可以读取和写入数据,所有数据都通过 Buffer 对
象来处理。我们永远不会将字节直接写入通道中,相反是将数据写入包含一个
或者多个字节的缓冲区。同样不会直接从通道中读取字节,而是将数据从通道
读入缓冲区,再从缓冲区获取这个字节。通道与流的不同之处在于通道是双向
的。而流只是在一个方向上移动(一个流必须是 InputStream 或者
OutputStream 的子类,比如 InputStream 只能进行读取操作,OutputStream
只能进行写操作),而通道是双向的,可以用于读、写或者同时用于读写。 <br>
![05_11_3](/data/images/Java应届生面试突击/Java基础/05_11_3.png) <br>

&ensp;&ensp;&ensp;&ensp;
    从图中可以看出,当有读或写等任何注册的事件发生时,可以从 Selector
中获得相应的 SelectionKey,同时从 SelectionKey 中可以找到发生的事件和该
事件所发生的具体的 SelectableChannel,以获得客户端发送过来的数据。 <br>
三. 选择器(Selector) <br>
&ensp;&ensp;&ensp;&ensp;
    NIO 有一个主要的类 Selector,这个类似一个观察者,只要我们把需要探知
的 socketchannel 告诉 Selector,我们接着做别的事情,当有事件发生时,他会
通知我们,传回一组 SelectionKey,我们读取这些 Key,就会获得我们刚刚注册
过的 socketchannel,然后,我们从这个 Channel 中读取数据,放心,包准能
够读到,接着我们可以处理这些数据。 <br>
    Selector 内部原理实际是在做一个对所注册的 channel 的轮询访问,不断
地轮询,一旦轮询到一个 channel 有所注册的事情发生,比如数据来了,他就
会站起来报告,交出一把钥匙,让我们通过这把钥匙来读取这个 channel 的内
容。 <br>
 &ensp;&ensp;&ensp;&ensp;
   Selector 的作用就是用来轮询每个注册的 Channel,一旦发现 Channel 有注
册的事件发生,便获取事件然后进行处理。用单线程处理一个 Selector,然后
通过 Selector.select()方法来获取到达事件,在获取了到达事件之后,就可以逐
个地对这些事件进行响应处理。 <br>
&ensp;&ensp;&ensp;&ensp;
    Selector 类是 NIO 的核心类, Selector 能够检测多个注册的通道上是否有事
件发生,如果有事件发生,便获取事件然后针对每个事件进行相应的响应处理。
这样一来,只是用一个单线程就可以管理多个通道,也就是管理多个连接。这
样使得只有在连接真正有读写事件发生时,才会调用函数来进行读写,就大大
地减少了系统开销,并且不必为每个连接都创建一个线程,不用去维护多个线
程,并且避免了多线程之间的上下文切换导致的开销。 <br>
![05_11_4](/data/images/Java应届生面试突击/Java基础/05_11_4.png) <br>

&ensp;&ensp;&ensp;&ensp;
    Java NIO 的服务端只需启动一个专门的线程来处理所有的 IO 事件,这种通
信模型是怎么实现的呢?java NIO 采用了双向通道(channel)进行数据传输,
而不是单向流(stream),在通道上可以注册我们感兴趣的事件。一共有以下
四种事件:

            事件名                    对应值
    服务端接收客户端连接事件  SelectionKey.OP_ACCEPT(16)
    客户端连接服务端事件     SelectionKey.OP_CONNECT(8)
    读事件                 SelectionKey.OP_READ(1)
    写事件                 SelectionKey.OP_WRITE(4)

&ensp;&ensp;&ensp;&ensp;
    服务端和客户端各自维护一个管理通道的对象,我们称之为 selector,该对
象能检测一个或多个通道(channel)上的事件。我们以服务端为例,如果服务
端的 selector 上注册了读事件,某时刻客户端给服务端送了一些数据,阻塞 I/O
这时会调用 read()方法阻塞地读取数据,而 NIO 的服务端会在 selector 中添加
一个读事件。服务端的处理线程会轮询地访问 selector,如果访问 selector 时发
现有感兴趣的事件到达,则处理这些事件,如果没有感兴趣的事件到达,则处
理线程会一直阻塞直到感兴趣的事件到达为止。下面是我理解的 java NIO 的通
信模型示意图: <br>

![05_11_5](/data/images/Java应届生面试突击/Java基础/05_11_5.png) <br>


### <a name="12">12. 面向对象的 6 个基本原则(设计模式的 6 个基本原则)。</a>
s( Single-Resposibility Principle ): 单一职责原则。 <br>
o( Open-Closed principle ): 开放封闭原则。 <br>
l( Liskov-Substituion Principle ): 里氏替换原则。 <br>
i( Interface-Segregation Principle ): 接口隔离原则。 <br>
d( Dependecy-Inversion Principle ): 依赖倒置原则。 <br>
    合成/聚合复用。 <br>
&ensp;&ensp;&ensp;&ensp;
    单一职责:是指一个类的功能要单一,一个类只负责一个职责。一个类只
做它该做的事情(高内聚)。在面向对象中,如果只让一个类完成它该做的事,而
不涉及与它无关的领域就是践行了高内聚的原则。 <br>
&ensp;&ensp;&ensp;&ensp;
    开放封闭:软件实体应当对扩展开放,对修改关闭。对扩展开放,意味着
有新的需求或变化时,可以对现有代码进行扩展,以适应新的情况。对修改封
闭,意味着类一旦设计完成,就可以独立其工作,而不要对类尽任何修改。在
开发阶段,我们都知道,如果对一个功能进行扩展,如果只是一味地对方法进
行修改,可能会造成一些问题,诸如可能会引入新的 bug,或者增加代码的复
杂度,对代码结构造成破坏、冗余,还需要重新进行全面的测试。那么该怎么
解决这些问题?很简单,这就需要系统能够支持扩展,只有扩展性良好的系统,
才能在不进行修改已有实现代码的基础上,引进新的功能。 <br>
&ensp;&ensp;&ensp;&ensp;
    里氏替换:任何使用基类的地方,都能够使用子类替换,而且在替换子类
后,系统能够正常工作。子类一定是增加父类的能力而不是减少父类的能力,
因为子类比父类的能力更多,把能力多的对象当成能力少的对象来用当然没有
任何问题。 一个软件实体如果使用的是一个基类,那么当把这个基类替换成继
承该基类的子类,程序的行为不会发生任何变化。软件实体察觉不出基类对象
和子类对象的区别。 <br>
&ensp;&ensp;&ensp;&ensp;
    接口隔离: 即应该将接口粒度最小化,将功能划分到每一个不能再分的子
角色,为每一个子角色创建接口,通过这样,才不会让接口的实现类实现一些
不必要的功能。 建立单一的接口,不要建立臃肿的庞大的接口,也就是说接口
的方法尽量少。接口要小而专,绝不能大而全。臃肿的接口是对接口的污染,
既然接口表示能力,那么一个接口只应该描述一种能力,接口也应该是高度内
聚的。 <br>
&ensp;&ensp;&ensp;&ensp;
    依赖倒置:即我们的类要依赖于抽象,而不是依赖于具体,也就是我们经
常听到的“要面向接口编程”。(该原则说得具体一些就是声明方法的参数类
型、方法的返回类型、变量的引用类型时,尽可能使用抽象类型而不用具体类
型,因为抽象类型可以被它的任何一个子类型所替代) 。 依赖倒置原则的本质
就是通过抽象(抽象类或接口)使各个类或模块的实现彼此独立,不相互影响,
实现模块间的松耦合。减少类间的耦合性。 <br>
&ensp;&ensp;&ensp;&ensp;
    合成/聚合复用:优先使用聚合或合成关系复用代码。
    
### <a name="13">13. JDK 源码中用到的设计模式 。</a>
1.单例模式: java.lang.Runtime 。 <br>
&ensp;&ensp;&ensp;&ensp;
    Runtime 类封装了 Java 运行时的环境。每一个 java 程序实际上都是启动
了一个 JVM 进程,那么每个 JVM 进程都是对应这一个 Runtime 实例,此实例
是由 JVM 为其实例化的。每个 Java 应用程序都有一个 Runtime 类实例,使
应用程序能够与其运行的环境相连接。由于 Java 是单进程的,所以,在一个 JVM
中,Runtime 的实例应该只有一个。所以应该使用单例来实现。一般不能实例
化一个 Runtime 对象,应用程序也不能创建自己的 Runtime 类实例,但可以
通过 getRuntime 方法获取当前 Runtime 运行时对象的引用。 <br>
2.享元模式:String 常量池和 Integer 等包装类的缓存策略:Integer.valueOf(int
i)等。 <br>
3.原型模式:Object.clone;Cloneable。 <br>
4.装饰器模式:IO 流中。 <br>
5.迭代器模式:Iterator 。 <br>

### <a name="14">14. 执行 Student s = new Student();在内存中做了哪些事情?</a>
1.类加载的过程。 <br>
2.对象初始化的顺序(对象实例化的过程)。 见 P28 <br>
3.在栈内存为 s 开辟空间,把对象地址赋值给 s 变量 。 <br>

### <a name="15">15. 你知道的开源软件有哪些?</a>
1.JDK <br>
2.Eclipse <br>
3.Tomcat <br>
4.MySQL <br>

### <a name="16">16. String 型变量如何转成 int 型变量,反过来呢?</a>
String num =“1000′′; <br>
int id=Integer.valueOf(num); <br>
—————————————— <br>
Int a=1000; <br>
String string=String.valueOf(a); <br>

### <a name="17">17. 怎么判断数组是 null 还是为空?</a>
&ensp;&ensp;&ensp;&ensp;
    输出 array.length 的值,如果是 0,说明数组为空。如果是 null 的话,会抛出
空指针异常。 <br>

### <a name="18">18. 怎样让一个线程放弃锁。</a>
Object.wait(); <br>
condition.await(); <br>

### <a name="19">19. IO 里面常见的类。</a>
![05_19_1](/data/images/Java应届生面试突击/Java基础/05_19_1.png) <br>

### <a name="20">20. xml 解析方式。</a>
DOM 和 SAX 的不同: <br>
&ensp;&ensp;&ensp;&ensp;
    1. DOM 是基于内存的,不管文件有多大,都会把 xml 文档都读到内存中,
从而消耗很大的内存空间。而 SAX 解析 xml 文件采用的是事件驱动的方式,当
某个事件被触发时,获取相应的 XML 的部分数据读到内存进行解析,只占用了
少量的内存空间。 <br>
&ensp;&ensp;&ensp;&ensp;
    2. DOM 可以读取 XML,也可以向 XML 文件中插入数据,而 SAX 却只能对
XML 进行读取,而不能在文件中插入数据。 <br>
&ensp;&ensp;&ensp;&ensp;
    3.DOM 可以指定要访问的元素进行随机访问,而 SAX 则不行。SAX 是从文
档开始执行遍历的,并且只能遍历一次。也就是说不能随机访问 XML 文件,只
能从头到尾的将 XML 文件遍历一次,但可以随时停止解析。 <br>


---
### 搬运工信息
Author:Jason Lou <br>
Email:vip.iotworld@gmail.com <br>
Blog:https://blog.csdn.net/qq_21508727 <br>
Github:https://github.com/JGPY/JavaGuideBooster <br>
---