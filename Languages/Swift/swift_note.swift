<<<<<<< HEAD
//来源：https://swift.org/

/*Basic
一、基础
1.变量和常量
    1.1变量声明和定义
        var a = 0   //定义了一个变量a，并赋值a=0
        var a = 0, b = 0, c = 0 //一行定义多个变量
    1.2指定变量类型
        声明变量时，在变量名后加冒号+空格+变量名，指定变量类型
        var welcomeMessage: String  //声明了一个变量，名叫welcomeMessage，类型为String
        var red, green, blue: Double    //一行声明多个同种类型的变量
        如果变量有初始值，Swift会自动猜测变量的类型
    1.3常量的声明和定义
        let a = 0   //定义了一个常量，并赋值a=0
        常量的值定义后不可被改变
    1.4变量和常量的命名
        变量和常量名不能包含：空格、数学符号、箭头、私有Unicode标量、短横-、box-drawing字符，不能以数字开头
    1.5输出
        var friendlyWelcome="Bonjour!"
        print(friendlyWelcome)          //输出friendlyWelcome字符串的值，输出：Bonjour!

        在一个字符串中，Swift使用字符串插补来包含变量名或常量名。将变量名/常量名用圆括号括起来，并在圆括号前加反斜杠“\”
        print("The current value of friendly Welcome is \(friendlyWelcome)")    //输出：The current value of friendlyWelcome is Bonjour!
    1.6类型安全
        Swift是一个类型安全的语言，会在编译中自动检查变量的类型是否匹配
    1.7类型推断
        Swift会自动猜测变量的类型
2.注释
    2.1单行注释
        //这是一行注释
    2.2多行注释
        /*
            多行注释用一对/*，*/包含
        */
        Swift中的多行注释可以嵌套。
        /*
            /*
                嵌套的注释
            */
        */
3.分号
    Swift的语句不需要加分号表示结束，但在一行写多个语句的情况下需要加分号“;”分开
4.变量
    4.1整形
        Swift提供了8,16,32,64位的有符号和无符号整形变量，要指定整形的位数，在Int或UInt后+相应位数（如Int32，UInt8），所有的类型名首字母需大写
        4.1.1范围
            可以用整形类型的min和max的属性来查看各个整数类型的最小和最大值
            let minValue = UInt8.min    //minValue是一个UInt8类型的常量，值为0
            let maxValue = UInt8.max    //maxValue是一个UInt8类型的常量，值为255
        4.1.2有符号整形Int
            大多数情况下不需要指定整形的位数，Int表示当前使用平台（32位或64位）的默认长度
            32位平台下，Int的范围是-2,147,483,648 ~ 2,147,483,647
        4.1.3无符号整形UInt
            与整形相同，UInt表示当前使用平台（32位或64位）的默认长度
    4.2浮点型
        4.2.1单精度浮点型Float
            32位
        4.2.2双精度浮点型Double
            64位
            双精度能提供至少15位小数
            给一个变量初始化并赋值小数，Swift会自动推断出变量的类型为Double
            给一个变量进行整数字面值和小数字面值混合运算，变量类型为Double
    4.3布尔型Bool
        取值：true，false
        布尔型不能向整形转换
    4.4元组
        元组使多种类型的多个数据整合成单一的混合值，元组内的多个数据的类型可以任意组合。
        用一对圆括号表示元组，用逗号和一个空格表示元组内的成员
        给元组赋值时使用一对圆括号括起来，数据间使用逗号和一个空格分隔
            let http404Error = (404, "Not Found")   //定义了一个名为http404Error的元组，包含了一个404的整形，和一个Not Found的字符串型
            let (statusCode, statusMessage) = http404Error  //用元组变量http404Error给元组常量(statusCode, statusMessage)赋值，statusCode = 404，statusMessage = "Not Found"
            print("The status code is \(statusCode)")       // 输出：The status code is 404
            print("The status message is \(statusMessage)") // 输出：The status message is Not Found
        在定义元组时可以对元组内的每个成员变量命名，用 冒号+空格+值 给元组成员分别赋值，成员间用逗号分隔
            let http200Status = (statusCode: 200, description: "OK")
        使用成员的值时使用成员运算符 . 
        print("The status code is \(http200Status.statusCode)")     // 输出：The status code is 200
        print("The status message is \(http200Status.description)") // 输出：The status message is OK
        用下划线代表一个元组成员取任意值
    4.5字面值
            整数字面值：
                十进制数，无前缀
                二进制数，0b开头
                八进制数，0o开头
                十六进制数，0x开头
            浮点数字面值：
                十进制数，无前缀，可选exp指数，表示基数×10^exp，用E或e表示。如：1.25e2=1.25*10^2=125.0
                十六进制数，0x开头，必须带exp指数，表示基数×2^exp，用P或p表示。如：0xFp2=15*2^2=60.0
            所有的字面值可以在数值前加0，数字中间加下划线_，方便阅读，不影响数值的大小
    4.6数值类型转换
        只有变量和常量才涉及强制类型转换，字面值不涉及，因为它没有类型
        整形<->整形：
            Swift不允许不同类型的数据做运算，必须显式做强制类型转换，格式为：类型(变量名)。如：let a: UInt8 = 1; let b: UInt16 = UInt16(a)
        整形<->浮点型：
            浮点型转整形，损失小数部分精度
    4.7类型别名
        可以定义一种类型别名，使其表示某种数据类型。格式：typealias 别名 = 现有数据类型
        typealias AudioSample = UInt16          //定义了类型为UInt16的一种类型别名 AudioSample
        var maxAmplitudeFound = AudioSample.min //AudioSample代表UInt16
    4.8字符与字符串
        4.8.1字符串String
            4.8.1.1字符串字面值
                字符串字面值用一对双引号""括起来，类型为String
                多行的字符串用一对三引号括起来（即以"""开始，以下一个"""结束），多行字符串内的一对单引号内的内容嵌套在三引号中，不算单独的字符串
                    let someString = """This
                    is
                    a
                    multiline
                    string.
                    """
                可以在多行字符串内的行末加反斜杠\，增强代码可读性，行末的反斜杠\不会出现在字符串中
                多行字符串的最后一行如果是结束的三引号，那么三引号前的空格数会使得多行字符串前面的每行消除相同的空格数
            4.8.1.2字符串字面值中的特殊字符
                4.8.1.2.1以反斜杠\开始的转义字符
                    \0： 空字符
                    \\： 一个反斜杠\
                    \t： 水平制表符tab
                    \n： 换行符（光标定位到行的最左边）
                    \r： 回车符（光标下移一行）
                    \"： 一个双引号"
                    \'： 一个单引号'
                    若要在多行字符串中表示三引号，至少要用一个\"代替其中三引号中的其中一个引号
                4.8.2.2强制Unicode转换字符
                    格式：\u{xxxxxxxx}，xxxxxxxx是1-8位十六进制数
            4.8.1.3字符串变量的初始化
                两种方法：
                var emptyString=""
                var anotherEmptyString = String()   //这里的String()实际上是字符串的构造函数，不加参数则构造一个空字符串
            4.8.1.4判断字符串是否为空
                格式：字符串名.isEmpty，返回一个布尔类型值
        4.8.2字符Character
            4.8.2.1字符字面值
                与字符串字面值相同，字符字面值也用一对双引号括起来，因此为了与字符串区分类型，在定义字符变量或常量时，需要显式指定类型
                let exclamationMark: Character = "!"    //定义了一个字符类型常量exclamationMark，值为"!"
            4.8.2.2用字符数组给字符串赋值
                可以用一个字符数组作为字符串的构造函数的参数
                let catCharacters: [Character] = ["C","a","t","!"]  //定义了一个字符数组catCharacters
                let catString = String(catCharacters)               //用catCharacters作String()的参数给字符串catString初始化
        4.8.3字符串和字符的合并操作
            用加号运算符+连接两个字符串，会生成一个新的合并后的字符串
            用自加运算符+=操作一个字符串变量，会将右操作数合并到字符串变量
            将一个字符加到字符串变量尾部，用方法：字符串名.append(字符变量/常量名)
        4.8.4字符串内插
            字符串内插用于将变量/常量的值代替字符串中的同名的变量/常量的名的字段，格式为：\(变量名) 

            



    4.9可空类型
        Swift提供一种可空类型，可空类型有两种可能：（1）如果这个类型的值存在，就等于这个值 （2）这个类型的值不存在
        可空类型的形式为：类型名?，如Int?
        问号?表示这个要么存在问号?前类型的值，要么不存在这个值
        例如：
            let possibleNumber = "123"                  //定义了一个字符串常量“123”
            let convertedNumber = Int(possibleNumber)   //将字符串转换为整数，然而并不是所有的字符串都能转换成一个整数，所以这里covertedNumber的类型自动推断为Int?型
    4.10空值nil
        所有的可空类型可以赋空值nil
        当声明了一个可空类型的变量却不初始化时，这个变量自动赋值为nil





二、运算符
    1.分类
        运算符有一元、二元、三元（Swift只有一种三元运算符——条件返回运算符：(a ? b : c)）
    2.赋值运算符=
        赋值运算符将右操作数的值赋给左操作数
        当右操作数为元组的成员形式（即用括号括起来的、用逗号和空格分开的成员变量）时，元组的成员分别给左操作数赋值
        与C不同，赋值表达式不带返回值
    3.算数运算符+，-，*，/
        这四个算术运算符适用于所有数值类型
        Swift默认不允许运算后的结果超过相应的类型范围
        +运算符作用于两个字符串，表示字符串合并
    4.求余运算符%
        a%b与a%-b结果相同
    5.自加、自减、自乘、自除运算符+=，-=，*=，/=
    6.比较运算符
        等于==
        不等于!=
        大于>
        小于<
        大于等于>=
        小于等于<=
        所有比较运算符返回一个布尔类型值来表明运算结果的真true与假false
        元组之间的比较，要求元组内的成员是可以比较的，比如布尔型就不能比较。
        两个元组做比较时，元组的成员从左到右依次比较，当所有成员的值与类型都相同时，两个元组相等。
        Swift标准库函数能支持最多7成员的元组做比较，当成员数>7时需要自己写函数实现。
    7.条件返回运算符
        question ? answer1 : answer2
        当question为真，返回answer1的值，否则返回answer2的值
    8.空值合并运算符

    9.范围运算符
        闭区间运算符，格式：a...b，表示a和b中间包括a和b的所有整数值
        半开区间运算符，格式：a..<b，表示a和b中间包括a的所有整数值
        单边运算符，格式：[a...]，表示取大于等于a的所有可能的非空的整数值；或[...a]，表示取小于等于a的所有可能的非空的整数值
        单边开区间运算符，格式：[..<a]，表示取小于a的所有可能的非空的整数值
    10.逻辑运算符
        10.1逻辑非!
        10.2逻辑且&&
        10.3逻辑非||
            注意逻辑且和逻辑非是短路运算符，意思是如果逻辑且的第一个表达式为假，则第二个表达式被短路，因为此时整个表达式必为假
                                        同理如果逻辑或的第一个表达式为真，则第二个表达式也被短路，因为此时整个表达式必为真
            组合逻辑在不加括号的前提下，从左到右顺序执行
    11.位运算符
        11.1按位取反 ~
        11.2按位与 &
        11.3按位或 |
        11.4按位异或 ^
        11.5左移操作符<<：格式： 操作数 << 左移的位数
        11.6右移操作符>>：格式： 操作数 >> 右移的位数
        


三、控制语句
1.条件判断语句
    1.1 if语句
        if 表达式
            {语句段}
        ————————————————
        if 表达式
            {语句段1}
        else
            {语句段2}
        ————————————————
        if 表达式1
            {语句段1}
        else if 表达式2
            {语句段2}
        else
            {语句段3}
        *所有的语句段的大括号不能省略
    1.2 switch语句
        在Swift中，switch只执行与表达式匹配的值的第一个case后的语句段，无需像C一样要加break来避免执行了多余的case
        每个case后的语句段不能省略不写
        格式：
            switch 表达式
            {
                case 值1:{语句段1}
                case 值2,值3:{语句段2}  //若表达式的值=2或3，执行语句段2
                default:{语句段3}       //可选，没有符合的值才执行
            }
        case后的值还可以是用范围运算符构成的值的区间，如：case 1..<5

        用switch比较元组的值：
            let somePoint = (1, 1)
            switch somePoint 
            {
                case (0, 0):
                    print("\(somePoint) is at the origin")
                case (_, 0):
                    print("\(somePoint) is on the x-axis")
                case (0, _):
                    print("\(somePoint) is on the y-axis")
                case (-2...2, -2...2):
                    print("\(somePoint) is inside the box")
                default:
                    print("\(somePoint) is outside of the box")
            }
        输出：(1, 1) is inside the box
        若somePoint = (0,0)，则输出case (0,0)的语句段，因为尽管其匹配所有case，Swift只执行与表达式匹配的值的第一个case的语句段

        switch用于局部变量的值绑定：
            当switch的表达式是一个值，且case中包含相应的局部变量时，某个case的局部变量会与表达式中的值部分匹配，从而赋值给局部变量，并执行case后的语句段
            let anotherPoint = (2, 0)
            switch anotherPoint 
            {
                case (let x, 0):
                    print("on the x-axis with an x value of \(x)")  //元组(2,0)与这个case部分匹配，从而x=2，并执行后面的print
                case (0, let y):
                    print("on the y-axis with a y value of \(y)")
                case let (x, y):
                    print("somewhere else at (\(x), \(y))")
            }
        输出：on the x-axis with an x value of 2
2.循环语句
    2.1 for-in循环
        for-in循环语句用于在一个序列（如数组，区间和字符串）中重复执行，每次执行时，for后的局部变量被赋值为序列中的某个元素的值，然后执行语句段
        格式1：for 局部变量名 in 序列 {语句段}  
        格式2：for _ in 序列 {语句段}            //如果语句段中不需要用到局部变量，可以省略，用下划线_代替
    2.2 while循环
        格式：while 条件 {语句段}
        while循环先判断条件是否为真，然后执行语句段，直到条件为假
    2.3 repeat-while循环
        格式：repeat {语句段} while 条件
        先执行语句段，然后判断条件是否为真，再执行语句段直到条件为假

四、函数
1.函数的定义
    func 函数名(参数名: 类型, 参数名: 类型 ...) -> 返回类型
    {函数体}
    如：
        func greet(person: String) -> String 
        {
            let greeting = "Hello, " + person + "!"
            return greeting
        }
    不带参数的函数： func 函数名() -> 返回类型
                    {函数体}
	
	多个返回值的函数：func 函数名(参数:类型...) -> (元组)
					{函数体}
	如：func minMax(array: [Int]) -> (min: Int, max: Int) 
	{
		var currentMin = array[0]
		var currentMax = array[0]
		for value in array[1..<array.count] {
			if value < currentMin {
				currentMin = value
			} else if value > currentMax {
				currentMax = value
			}
		}
		return (currentMin, currentMax)		//返回一个元组，元组包含两个整形成员，名叫min,max
	}

	返回可空类型的函数：func 函数名(参数:类型...) -> 返回类型?
						{函数体}
	如上例中的minMax函数，若参数的数组是空数组，那么返回的元组就是空值，故上例改写为：
		func minMax(array: [Int]) -> (min: Int, max: Int)?		//返回一个可空类型的元组(min: Int, max: Int)?
		{
			if array.isEmpty { return nil }
			var currentMin = array[0]
			var currentMax = array[0]
			for value in array[1..<array.count] {
				if value < currentMin {
					currentMin = value
				} else if value > currentMax {
					currentMax = value
				}
			}
			return (currentMin, currentMax)
		}
2.函数的调用
	Swift中的函数调用，必须在实参前加定义函数时的形参名
	如：func someFunction(firstParameterName: Int, secondParameterName: Int)		//定义了一个函数，函数的第一个形参名firstParameterName，第二个形参名secondParameterName
		{函数体}
		someFunction(firstParameterName: 1, secondParameterName: 2)				//调用someFunction，并将1赋值给第一个形参，2赋值给第二个形参

	函数定义时可以给形参一个别名，调用时用这个形参的别名，格式：func 函数名(形参别名 形参: 类型)
	如：func greet(person: String, from hometown: String) -> String			//第二个形参hometown的别名是from
	{
		return "Hello \(person)!  Glad you could visit from \(hometown)."
	}
	print(greet(person: "Bill", from: "Cupertino"))							//调用greet，"Bill"赋值给第一个形参person,"Cupertino"赋值给第二个形参hometown

	函数定义时可以给形参一个空的别名，调用时不写任何形参名，直接按顺序给形参传递值
	如：func someFunction(_ firstParameterName: Int, secondParameterName: Int)		
		{函数体}
		someFunction(1, secondParameterName: 2)									//函数的第一个形参有空的别名，所以调用时第一个值传递给第一个形参
3.形参的初始值
	可以在函数的定义时给形参赋初始值，这样调用函数时如果没有实参给形参传递值，就使用定义函数中的形参的初始值
	格式：func 函数名(参数: 类型 = 初始值)
			{函数体}
	如：func someFunction(parameterWithoutDefault: Int, parameterWithDefault: Int = 12)	//第二个参数的初始值为12
			{}
		someFunction(parameterWithoutDefault: 3, parameterWithDefault: 6)				//调用值完整，所以将6覆盖掉第二个参数的初始值
		someFunction(parameterWithoutDefault: 4)										//调用时缺少第二个参数的值，所以使用其默认值12
4.可变参数
	可以在定义函数时定义可变的形参列表，这样使得调用函数时，形参接收实参的值，形成一个数组，一个函数最多只能有一个可变参数
	格式：func 函数名(_ 参数名: 类型...) -> 返回值类型	//在参数名的类型后紧跟3个点，表示这个参数是可变参数，在函数体内充当数组
			{函数体}								 //下划线_表示调用函数时不写参数名




	

五、闭包
1.闭包的类型
	闭包有以下三种形式：
		（1）全局函数是一种闭包，有名字，不捕获任何值
		（2）局部函数是一种闭包，有名字，能捕获定义他的外部函数的值
		（3）闭包表达式是一种轻量化的闭包，没有名字，能捕获包围他的上下文中的值
2.闭包表达式
	2.1形式：
		{(参数: 类型) -> 返回值类型 in {语句段}
		}
        Swift标准库中提供一种方法sorted(by:)，by:后需要调用一种闭包(类型, 类型) -> Bool 来处理排序，如要处理多个字符串的排序，按字符串相反于字母表顺序排序，可以使用这个方法：
            第一种闭包写法：
                let names = ["Chris", "Alex", "Ewa", "Barry", "Daniella"]   //定义了一个字符串数组names
                func backward(_ s1: String, _ s2: String) -> Bool           //定义了一个函数backward，它属于第一种闭包
                {
                    return s1 > s2                                          //若s1>s2，即s1字符串（第一个字母相同则比较第二个，直至不同）的字母比s2大，这个函数返回true，所以整个字符串从大到小排序
                }
                var reversedNames = names.sorted(by: backward)              //调用sorted(by:)方法，并将结果存于reversedNames中

            闭包表达式写法：
                let names = ["Chris", "Alex", "Ewa", "Barry", "Daniella"]
                var reversedNames = names.sorted(by:{(s1: String, s2: String) -> Bool in {return s1 > s2}}) //闭包表达式为：{(s1: String, s2: String) -> Bool in {return s1 > s2}}，其类型为(String, String) -> Bool
    2.2闭包表达式的类型推断
        当闭包表达式作为函数或方法的参数时，Swift会自动推断出闭包的参数类型和返回值类型，所以闭包表达式中的参数的类型和返回值的类型可以省略不写
        如上例闭包表达式可以进一步简写为：
            var reversedNames = names.sorted(by: { s1, s2 in {return s1 > s2} })    //省略了s1，s2的类型String，和返回值类型Bool
        又由于这里闭包表达式的语句段部分只有一行，所以语句段的一对花括号可以省略，简写为：
            var reversedNames = names.sorted(by: { s1, s2 in return s1 > s2 })
    2.3闭包表达式的隐式返回
        当闭包表达式的语句段部分只有一行时，return关键词可以省略
        如上例中的闭包表达式，Swift会推断出要返回一个布尔类型值，而且语句段部分只有一行，所以return的内容很明确，可省略return关键字，简写为：
            var reversedNames = names.sorted(by: { s1, s2 in s1 > s2 } )
    2.4闭包表达式的参数缩写
        可以用$0,$1...代替传递给闭包表达式的第1,2...个参数，并省略闭包表达式的参数列表
        如上例可以进一步简写为：
            var reversedNames = names.sorted(by: { $0 > $1 } )  //传递给闭包表达式的两个分别赋值给$0，$1，并返回($0 > $1)的布尔值
    2.5操作符写法
        Swift的>运算符对字符串提供了一种特殊方法，这个方法接收两个字符串，然后返回布尔值，这正是sorted(by:)需要的方法，所以可以把一个大于号“>”作为闭包表达式
        如上例可以进步一简写为：
            var reversedNames = names.sorted(by: >)
    2.6尾随闭包
        在需要在调用函数时用闭包作为函数参数之一，而闭包又太长，可以用尾随闭包的形式调用函数，尾随闭包写在调用函数的括号之后，并且不用给尾随闭包写出参数名和参数别名，格式
            func someFuncThatTakesAClosure(closure: () -> Void)             //定义了一个闭包作为参数之一的函数
            {}

            someFuncThatTakesAClosure(closure: {() -> Void in {语句段}})    //用正常调用函数的形式将闭包传递给函数的闭包参数
            someFuncThatTakesAClosure()                                     //用尾随闭包的形式调用函数，闭包写在调用函数的括号之后
            {
                () -> Void in {语句段} //这是闭包
            }
        所以上例在调用sorted(by:)传递给他的闭包可以写成尾随闭包的形式：
        var reversedNames = names.sorted() {$0 > $1}
        
        如果一个尾随闭包是调用函数时的唯一参数，可以省略调用函数的括号，直接在函数名后加尾随闭包
        上例可以进一步简写为：
        var reversedNames = names.sorted {$0 > $1}
3.闭包捕获值
    闭包能捕获值的意思就是在闭包内，能直接引用包含了闭包的外围函数内的某些变量
4.闭包是一种引用类型
    意思是你可以把一个闭包同时赋值给两个变量或常量，那么这两个变量或常量就是同一个闭包的引用，他们的值是相等的，都等于同一个闭包，所以他们的值（就是同一个闭包）的内容（闭包的内容）也是相等的
5.逃逸闭包
    如果一个闭包作为参数传递给函数，但是在函数返回之后才被调用，那么这个闭包称为逃逸闭包

    //?
6.自动闭包
    //?

六、枚举
枚举类型是一种将一组有关联的值合并到一起的类型，并根据情况，取且只能取有限个值
1.枚举类型的定义
    在枚举类型名称前加关键字enum，枚举类型的内容用一对大括号括起来，里面的各个取值前用关键字case和一个空格分隔
    枚举类型名的首字母最好大写，名字最好用单数而不是复数
    Swift中的枚举类型在定义时不初始化
    enum CompassPoint {     //定义了一个枚举类型叫CompassPoint，包含四个取值
    case north
    case south
    case east
    case west
    }

    多个成员可以写在一行，用逗号和空格分隔
    enum CompassPoint {case north, south, east, west}

    定义一个枚举类型的变量并初始化时，Swift将自动推断这个变量的类型是枚举类型
    将一个枚举类型赋值给一个变量后，下次改变这个变量的值为枚举类型的其他值，不需要再写出枚举类型名，用一个点.代替其类型名，如：
    var direction = CompassPoint.west   //定义了一个CompassPoint类型的枚举变量，并初始化赋值为west
    direction = .east                   //改变这个枚举变量的值为CompassPoint类型的east
2.枚举类型与switch语句
    switch 枚举类型变量
    {
        case .值1: {语句段1}
        case .值2: {语句段2}
        ...
    }
    由于switch语句需要列出所有情况，所以如果枚举类型的所有取值没有在switch case语句中全部列出，会使得编译错误
    可以在switch语句里加入default分支（与switch语句的其他用法相同）
3.枚举类型的遍历
    如果要使枚举类型取遍所有值，要在定义枚举类型时在枚举类型名后加关键字: CaseIterable，在使用这个枚举类型时加.allCases属性就会返回其所有值形成的数组，如
    enum Beverage: CaseIterable
    {case coffee, tea, juice}                       //定义了一个叫Beverage的枚举类型，可以取遍其所有值
    let numberOfChoices = Beverage.allCases.count   //Beverage.allCases返回一个数组，包含了Beverage的所有可能值，再加.count，返回这个数组的元素个数，所以这里numberOfChoices=3
    for beverage in Beverage.allCases
    {
        print(beverage)                             //遍历Beverage中的所有取值，并打印输出
    }
4.取不同类型作为取值的枚举类型
    可以将不同的类型作为一个枚举类型的取值
    enum Barcode                        //定义了一个Barcode枚举类型，包含两种取值，一种取值是元组(Int, Int, Int, Int)类型，一种取值是元组(String)类型
    {
        case upc(Int, Int, Int, Int)    
        case qrCode(String)
    }
    var productBarcode = Barcode.upc(8, 85909, 51226, 3)    //定义了一个productBarcode类型的枚举变量，其值是upc

    可以在switch语句中的case分支提取一个将不同类型作为取值的枚举类型的变量的值
    switch productBarcode 
    {
        case .upc(let numberSystem, let manufacturer, let product, let check):
            print("UPC: \(numberSystem), \(manufacturer), \(product), \(check).")
        case .qrCode(let productCode):
            print("QR code: \(productCode).")
    }
    如果在一个case分支里提取的枚举类型的变量的值全部作为常量或变量，可以将let或var关键字写在case关键字之后，枚举类型的取值之前
    如上例可以写成：
        switch productBarcode 
        {
            case let .upc(numberSystem, manufacturer, product, check):
                print("UPC : \(numberSystem), \(manufacturer), \(product), \(check).")
            case let .qrCode(productCode):
                print("QR code: \(productCode).")
        }
5.预定义值
    5.1显示预定义值
        枚举类型可以预定义默认值，如
        enum ASCIIControlCharacter: Character   //定义了一个情况都是字符型的枚举类型，并预定义了情况的取值
        {
            case tab = "\t"                     //当ASCIIControlCharacter = .tab时，他的值是"\t"
            case lineFeed = "\n"
            case carriageReturn = "\r"
        }
    5.2隐式预定义值
        当枚举类型在定义时Swift会自动给各个成员赋值
        当枚举类型的成员都是Int型时，Swift自动给各个成员赋值0,1,2,3...。如果预定义了第一个成员的值，Swift自动给下面的各个成员按顺序赋+1后的值，如
            enum Planet: Int 
            {
                case mercury = 1, venus, earth, mars, jupiter, saturn, uranus, neptune  //venus=2,earth=3...以此类推
            }
        
        当枚举类型的成员都是String型时，Swift自动给各个成员赋值其名字的字符串字面值，如：
        enum CompassPoint: String 
        {
            case north, south, east, west   //north = "north",south = "south"...以此类推
        }
    5.3访问枚举变量成员的预定义值
        用枚举变量成员的.rawValue属性访问，如：
            let sunsetDirection = CompassPoint.west.rawValue    //sunsetDirection = "west"
6.递归枚举
    在一个枚举类型里包含了其他枚举类型的成员值，称为递归枚举
    在定义递归枚举时，需要在其枚举类型的成员值的case关键字前加indirect关键字

七、结构体和类
1.结构体和类的比较
    在Swift中，结构体和类都可以：
        （1）定义属性来存储值
        （2）定义方法
        （3）定义下标来访问值
        （4）定义构造函数来提供初始值
        （5）扩展自身的功能
        （6）遵循协议来提供某种标准功能
    以下特性，类有，而结构体没有：
        （1）继承，使得一个类能拥有另一个类的特性
        （2）类型转换使得可以在运行时检查和转换一个类的类型
        （3）析构函数，让一个实体释放资源
        （4）引用计数，使得可以对一个实体引用多次
2.定义
    用struct关键字定义结构体，用class关键字定义类，结构体名、类名首字母最好大写
        struct SomeStructure {}
        class SomeClass {}
3.实体的定义
    定义结构体和类的实体与定义变量或常量的方式相同，用赋值语句，在结构体名和类名后加一对圆括号
    注意类和结构体的实体名与类和结构体本身的名字不能相同
        var someInstance = SomeStructure()
4.访问属性
    用点.操作符来访问一个实体的属性，点.操作符的后面是属性名
    可以用点.操作符来对一个实体的属性赋值
5.结构体对成员变量的初始化
    所有的结构体都会在定义时自动生成一个对成员变量的初始化函数，你可以用自动生成的初始化函数对新的结构体的实体赋初始值
    在定义实体时，在结构体名后的一对圆括号里写：成员变量名: 初始值，成员变量之间用逗号, 和空格分隔，如：
        let vga = Resolution(width: 640, height: 480)   //对一个Resolution的实体vga的width和height属性（成员）赋值
6.结构体和枚举类型是值的类型
    值的类型是当他们对变量或常量赋值或者作为参数进行函数调用时，实体的值会被复制，从而形成了两个单独的实体
    目前为止，所有的基本类型：整形、浮点型、布尔型、字符串型、数组型、字典都是值型
7.类是引用类型
    7.1引用类型的特性
        引用类型是当他们对一个变量或常量赋值，或是作为参数传递给一个函数时，实际上是形成了一个新引用
        变量和常量引用一个类，实际上称为了这个类的实体的一个别名，类的实体作为参数传递给函数时，实际上是形参称为了这个实体的一个别名
        对这个实体进行更改，所有引用它的变量、常量、形参的值都会改变
    7.2判断引用是否是对同一个实体的引用
        用三等号===操作符，判断两个引用是否是对同一个类的实体的引用；用!==操作符判断是否不是对同一个实体的引用
        这两个操作符的结果都是布尔值

八、属性
1.存储属性
    1.1存储属性的定义
        最简单的存储属性是在类或结构体里内，用var或let关键字定义的变量或常量
    1.2常量实体的存储属性
        如果将一个结构体的实体用let关键字赋值给一个常量，那么他的任何存储属性都不能被修改，如：
            struct FixedLengthRange{                                            //定义了一个结构体FixedLengthRange，包含两个Int类型的存储属性
                var firstValue: Int
                let length: Int
            }   
            let rangeOfFourItems = FixedLengthRande(firstValue: 0, length: 4)   //定义了一个常量实体rangeOfFourItems，并对其中的存储属性的值进行初始化
            rangeOfFourItems.firstValue = 6 //编译时报错，不可以改变常量实体的存储属性的值
        对于类，即使将类的一个实体赋值给一个常量，也可以改变其中的存储属性的值，因为类是引用类型
    1.3延迟存储属性
        延迟存储属性是定义其一个实体时不对其值进行初始化，直到使用时才赋值的属性，也就是说一个延迟存储属性不使用他，他不存在
        在定义前加lazy关键字定义一个延迟存储属性，如：
            class DataImporter {
                var filename = "data.txt"
                ...                         //定义了一个DataImporter类，其他函数省略
            }

            class DataManager {
                lazy var importer = DataImporter()  //定义了一个DataImporter类的实体为延迟存储属性，
                var data = [String]()
                ...                                 //DataManager类的其他函数省略
            }
            let manager = DataManager()             //定义了一个DataManager类的实体
            manager.data.append("Some data")        //写入一些数据
            manager.data.append("Some more data")   //写入更多数据
            //到此为止，manager中的importer属性并没有产生，因为其被定义为延迟存储属性，而且未被使用
            print(manager.importer.filename)        //到此，manager中的importer属性才产生了，输出：data.txt
 2.计算属性
    2.1计算属性的定义
        类、结构体、枚举类型可以定义计算属性，计算属性不存储值，而是提供了get和set方法来取出或更改其他存储属性的值
        所有的计算属性都必须用var关键字定义，因为他们的值不确定
            struct Point {
                var x = 0.0, y = 0.0
            }
            struct Size {
                var width = 0.0, height = 0.0
            }
            struct Rect {
                var origin = Point()
                var size = Size()
                var center: Point 
                {                                                   //center是一个计算属性，返回类型是Point类型
                    get {                                           //center这个计算属性的get方法
                        let centerX = origin.x + (size.width / 2)
                        let centerY = origin.y + (size.height / 2)
                        return Point(x: centerX, y: centerY)
                        }
                    set(newCenter) {                                //center这个计算属性的set方法，使用时接受一个Point类型的值
                        origin.x = newCenter.x - (size.width / 2)
                        origin.y = newCenter.y - (size.height / 2)
                    }
                }
            }
            var square = Rect(origin: Point(x: 0.0, y: 0.0),
                            size: Size(width: 10.0, height: 10.0))  //定义了一个Rect的实体square，并对一些存储属性初始化
            let initialSquareCenter = square.center                 //调用了square的计算属性center的get方法，get方法计算并返回一个Point类型值，所以initialSquareCenter = (x: 5, y: 5)
            square.center = Point(x: 15.0, y: 15.0)                 //调用了square的计算属性center的set方法，set方法计算并对square内的其他存储属性赋值
            print("square.origin is now at (\(square.origin.x), \(square.origin.y))")
            // 输出：square.origin is now at (10.0, 10.0)
    2.2简写计算属性的set方法
        如果计算属性的set方法没有定义一个接受新值的变量，则会隐式使用一个名字叫newValue的名字
        如上例的center计算属性的set(newCenter)，如果没有定义newCenter来接受新值，会隐式使用newValue，即上例的Rect可以改写为：
            struct AlternativeRect 
            {
                var origin = Point()
                var size = Size()
                var center: Point {
                    get {
                        let centerX = origin.x + (size.width / 2)
                        let centerY = origin.y + (size.height / 2)
                        return Point(x: centerX, y: centerY)
                    }
                    set {                                       
                        origin.x = newValue.x - (size.width / 2)
                        origin.y = newValue.y - (size.height / 2)
                    }
                }
            }
    2.3只读计算属性
        一个只有get没有set的计算属性是只读计算属性，只读计算属性总是只返回一个计算结果
        只读计算属性的定义由于只有get，所以可以省略get关键字和他的一对花括号，如：
            struct Cuboid {
            var width = 0.0, height = 0.0, depth = 0.0
            var volume: Double {                        //定义了一个只读计算属性volume
                return width * height * depth           
            }
        }
        let fourByFiveByTwo = Cuboid(width: 4.0, height: 5.0, depth: 2.0)   //初始化一个Cuboid的实体fourByFiveByTwo，并对一些存储属性赋值
        print("the volume of fourByFiveByTwo is \(fourByFiveByTwo.volume)") //调用这个实体的volume只读计算属性
        // 输出：the volume of fourByFiveByTwo is 40.0
3.属性观察器
    属性观察器会观察属性的值，并在属性的值改变时（即使是重新赋一个跟原来相同的值）做出反应
    有两种属性观察器：willSet，在赋值前被调用
                    didSet，在赋值后被调用
    在一个所要观察的存储属性的定义后跟一对花括号，写willSet和didSet函数
    3.1willSet的使用
        在定义一个willSet观察器时，给属性赋新值时，新值会作为一个常量参数传递给观察器
        如果没有显式写出willSet观察器的参数名和一对圆括号，那么会自动默认使用名为newValue的常量参数
    3.2didSet的使用
        在定义一个didSet观察器时，给属性赋新值时，这个属性的原值会作为一个常量参数传递给观察器
        如果没有显式写出didSet观察器的参数名和一对圆括号，那么会自动默认使用名为oldValue的常量参数
        如果在didSet函数中对属性有赋值操作，那么对属性赋新值时，didSet中的赋值会覆盖掉所赋的新值
            class StepCounter 
            {
                var totalSteps: Int = 0 
                {
                    willSet(newTotalSteps) 
                    {
                        print("About to set totalSteps to \(newTotalSteps)")
                    }
                    didSet                                                      //没有显式写出didSet的参数名，所以默认使用oldValue作为参数名
                    {
                        if totalSteps > oldValue  
                        {
                            print("Added \(totalSteps - oldValue) steps")
                        }
                    }
                }
            }
            let stepCounter = StepCounter()
            stepCounter.totalSteps = 200
            //输出：About to set totalSteps to 200
                    Added 200 steps
    3.3属性作为函数参数
        属性作为函数输入输出参数时，willSet和didSet总是会被调用，因为作为函数的输入输出参数时，属性会被拷贝进内存，函数执行完毕后再覆盖掉属性原来的值
4.全局与局部属性
    所有上述的属性的特性都适用于全局属性和局部属性
    全局属性是定义在函数、方法、闭包外的属性，包括前面涉及的各种全局变量
    全局变量和常量作为全局属性，他们总是作为延迟存储属性使用的，但是不需要加lazy关键字
    局部属性，除非定义为延迟存储属性，否则总是在定义时就产生（即分配内存）
5.类型属性
    可以定义一种属性，这种属性独立于任何实体，称为类型属性
    存储类型属性可以是变量或常量，计算类型属性必须是变量，就像定义在类或结构体实体中的计算属性那样，如：
        struct SomeStructure 
        {
            static var storedTypeProperty = "Some value."
            static var computedTypeProperty: Int 
            {
                return 1
            }
        }
        enum SomeEnumeration 
        {
            static var storedTypeProperty = "Some value."
            static var computedTypeProperty: Int 
            {
                return 6
            }
        }
        class SomeClass 
        {
            static var storedTypeProperty = "Some value."
            static var computedTypeProperty: Int 
            {
                return 27
            }
            class var overrideableComputedTypeProperty: Int 
            {
            return 107
            }
        }

九、方法
        方法是与一种特定类型相关联的函数，类、结构体、枚举类型都可以定义方法
        方法将一种类型需要执行的任务和实现的功能包裹起来
    1.实体的方法
        定义实体的方法与函数相同，把方法写在一个类、结构体、枚举类型的定义中，如：
            class Counter                           //定义了一个Counter类，包含一个变量count，和三个方法
            {
                var count = 0
                func increment() 
                {
                    count += 1
                }
                func increment(by amount: Int) 
                {
                    count += amount
                }
                func reset() 
                {
                    count = 0
                }
            }
        let counter = Counter() //定义了Counter类的一个实体counter
        1.1 self属性
            每一种类型的实体都存在一个隐式的属性叫self，self属性是在实体本身的方法中对自身的引用
            所以上例中Counter类的方法func increment()可以改写为：
                func increment()
                {
                    self.count +=1
                }
            当在一个实体中使用一个已知的方法名时，Swift总是推断你使用的是当前这个实体的方法，所以不需要显式写self

            一个例外的情况是一个方法的形参名跟实体内的某个变量名相同时，由于形参名在调用函数发生数据拷贝时优先级更高，所以需要显式写出self表示形参接受的是实体内那个与形参重名的属性名，如：
                struct Point 
                {
                    var x = 0.0, y = 0.0
                    func isToTheRightOf(x: Double) -> Bool 
                    {
                        return self.x > x               //返回一个布尔值，当这个实体内的x比形参大时，返回值为真
                    }
                }
                let somePoint = Point(x: 4.0, y: 5.0)   //定义了一个Point类的实体somePoint，初始化x=4，y=5
                if somePoint.isToTheRightOf(x: 1.0)     //调用somePoint实体的isToTheRightOf方法，并赋值给形参x=1.0
                {   
                    print("This point is to the right of the line where x == 1.0")  //由于self.x比形参的x大，所以输出这一行字符串
                }
                // 输出：This point is to the right of the line where x == 1.0
        1.2在实体的方法中更改值类型
            结构体和枚举类型是值类型，默认情况下，一个值类型的方法不能修改实体中定义的变量的值
            可以在方法前加mutating关键字，使得一个值类型的实体的方法可以改变这个实体内的变量的值，如：
                struct Point 
                {
                    var x = 0.0, y = 0.0
                    mutating func moveBy(x deltaX: Double, y deltaY: Double)    //mutating关键字使得结构体或枚举类型里的方法可以改变结构体或枚举类型内的变量 
                    {
                        x += deltaX                                             //Point内的成员x=x+deltaX
                        y += deltaY
                    }
                }
                var somePoint = Point(x: 1.0, y: 1.0)       //定义了一个Point类型的实体somePoint，初始化x=1.0，y=1.0
                somePoint.moveBy(x: 2.0, y: 3.0)            //调用somePoint的方法，给形参deltaX赋值2.0，deltaY赋值3.0
                print("The point is now at (\(somePoint.x), \(somePoint.y))")
                // 输出：The point is now at (3.0, 4.0)
            同样的，可以在mutating方法中使用self关键字来表示是对实体内成员变量的引用
            不可以对一个常量实体使用mutating来改变这个实体内的成员变量，如上例将somePoint用let关键字定义，调用moveBy方法会编译报错
    2.类型的方法
        实体的方法是在定义实体之后才能调用的方法，类型的方法是对一个类型的所有实体都适用的方法
        在方法之前用static关键字来表明这是一个类型的方法
        对于类，可以使用class关键字使得子类可以覆盖在父类中定义的方法
        调用类型的方法同样使用点.操作符，然而操作符的左操作数不是一个实体，而是一个类型名，格式： 类型名.类型的方法名
        在类型的方法中，同样有隐式的self关键字来表示对这个类的成员变量的引用，如：
            struct LevelTracker 
            {
                static var highestUnlockedLevel = 1     //定义了一个static的变量highestUnlockedLevel，表示这个变量的值在所有LevelTracker的实体中都相同
                var currentLevel = 1

                static func unlock(_ level: Int) 
                {
                    if level > highestUnlockedLevel { highestUnlockedLevel = level }
                }

                static func isUnlocked(_ level: Int) -> Bool 
                {
                    return level <= highestUnlockedLevel
                }

                @discardableResult
                mutating func advance(to level: Int) -> Bool 
                {
                    if LevelTracker.isUnlocked(level) 
                    {
                        currentLevel = level
                        return true
                    } 
                    else 
                    {
                        return false
                    }
                }
            }
            class Player 
            {
                var tracker = LevelTracker()        //Player类中包含一个LevelTracker的实体tracker
                let playerName: String
                func complete(level: Int) 
                {
                    LevelTracker.unlock(level + 1)
                    tracker.advance(to: level + 1)
                }
                init(name: String) 
                {
                    playerName = name
                }
            }
            var player = Player(name: "Argyrios")   //定义了一个Player的实体player，并通过init构造函数给其中的playerName成员赋值为Argyrios
            player.complete(level: 1)               //调用这个player实体的complete方法
            print("highest unlocked level is now \(LevelTracker.highestUnlockedLevel)")
            // 输出：highest unlocked level is now 2
            player = Player(name: "Beto")           //调用init构造函数给其中的playerName成员赋值为Beto
            if player.tracker.advance(to: 6)        //调用这个player实体的tracker实体中的advance方法
            {
                print("player is now on level 6")   //由于advance方法检查形参level是否unlocked，这里形参level=6，没有unlocked，所以返回假
            } 
            else 
            {
                print("level 6 has not yet been unlocked")
            }
            //输出：level 6 has not yet been unlocked

十、下标
    下标是访问一个集合、列表或序列中元素的快捷方式，可以用索引号来访问他们，而无需分别定义方法
    索引号用一对方括号括起来
    可以在类、结构体、枚举类型中定义下标
    可以对一种类型定义多个下标，也可以对多种不同的索引号使用重载方法，来对不同类型的索引号使用不同下标
    1.下标的语法
        用subscript关键字定义下标，用一对圆括号把形参括起来，set方法的newValue的类型与subscript的返回值类型必须相同
        subscript也有get和set(newValue)方法
            subscript(index: Int) -> Int    //这个下标返回一个整形值，所以get方法要返回一个整形值，set方法要接受一个整形值
            {
                get {
                    // return an appropriate subscript value here
                }
                set(newValue) {
                    // perform a suitable setting action here
                }
            }
        与计算属性类似，set的参数名可以省略不写，Swift会自动使用隐式的newValue作为set的参数
        只读的下标只有get方法，没有set方法，所以get关键字也可以省略不写，如：
            subscript(index: Int) -> Int    //这个下标返回一个整形值，所以get方法返回一个整形值
            {
                // return an appropriate subscript value here
            }
        例：
        struct TimesTable 
        {
            let multiplier: Int
            subscript(index: Int) -> Int 
            {
                return multiplier * index
            }
        }
        let threeTimesTable = TimesTable(multiplier: 3)
        print("six times three is \(threeTimesTable[6])")   //使用下标访问threeTimesTable，调用其中的subscript方法
        //输出： six times three is 18  
    2.下标的使用
        下标主要用于作为访问一个集合、列表、序列中元素的捷径
        例如Swift中的字典Dictionary类型提供了一种下标方法访问字典中的元素或者对他们赋值，可以通过与字典的索引相同的类型的值来访问一个元素，然后用对这个元素赋与元素相同类型的值
            var numberOfLegs = ["spider": 8, "ant": 6, "cat": 4]    //定义了一个numberOfLegs的字典，索引值是一个字符串，元素的值是一个整形数，所以这个字典的类型是[String: Int]
            numberOfLegs["bird"] = 2                                //给这个字典添加了一个项目 "bird": 2
            numberOfLegs["spider"]=nil                              //通过给一个元素赋值nil来删除这个元素，此时这个字典有3个元素
            print("numbers in this dictionary: \(numberOfLegs.count)")
            //输出：numbers in this dictionary: 3
    3.下标的重载
        一个类或结构体可以定义多个下标，根据实际的参数类型来调用不同的下标，称为下标重载
        下例是一个包含多参数下标的结构体Matrix：
        struct Matrix 
        {
            let rows: Int, columns: Int
            var grid: [Double]
            init(rows: Int, columns: Int)       //结构体Matrix的构造函数，接受一个(Int, Int)类型作为参数
            {
                self.rows = rows                //注意由于init构造函数的形参参数名与结构体内的成员变量重名，所以要显式写出self
                self.columns = columns
                grid = Array(repeating: 0.0, count: rows * columns) //Array中的元素全部初始化为0.0，这个一位数组长度为rows*columns
            }
            func indexIsValid(row: Int, column: Int) -> Bool 
            {
                return row >= 0 && row < rows && column >= 0 && column < columns
            }
            subscript(row: Int, column: Int) -> Double                                  //这个下标接受类型为[Int, Int]的参数，返回一个双精度浮点型
            {
                get {
                    assert(indexIsValid(row: row, column: column), "Index out of range")    //assert方法接受一个函数作为参数，来检查下标所接受的参数是否超出范围
                    return grid[(row * columns) + column]
                }
                set {
                    assert(indexIsValid(row: row, column: column), "Index out of range")
                    grid[(row * columns) + column] = newValue
                }
            }
        }
        var matrix = Matrix(rows: 2, columns: 2)    //定义了一个Matrix的实体matrix，并调用构造函数
        matrix[0, 1] = 1.5                          //访问并修改matrix中的元素

十一、继承
    一个类可以从其他类继承方法、属性和其他特性，被继承的类称为父类，继承他的类称为子类
    类可以访问和调用从父类继承而来的方法、属性和下标，并可以覆盖继承而来的方法、属性、下标，这些从而拥有新的方法、属性、下标
    Swift会检查所覆盖的内容，确保在父类中有对应被覆盖的内容的定义
    类也可以对继承而来的属性添加属性观察器，使得这些属性发生更改时执行相应的动作
    1.定义一个基类
        只要不是继承而来的类就是基类，用class关键字定义一个基类
            class SomeClass{}
    2.子类
        子类从基类继承方法、属性、下标，并添加自己的新特性
        要表示一个子类是从父类继承而来，需要在子类类名后加冒号:和空格，跟上父类的类名，格式：class SomeSubclass: SomeSuperclass{}
        class Vehicle                                                               //定义了一个基类Vehicle
        {
            var currentSpeed = 0.0
            var description: String 
            {
                return "traveling at \(currentSpeed) miles per hour"
            }
            func makeNoise() 
            {
            // do nothing - an arbitrary vehicle doesn't necessarily make a noise
            }
        }
        class Bicycle: Vehicle      //定义了Vehicle类的一个子类Bicycle，此时Bicycle继承了Vehicle的属性：currentSpeed（存储属性）、description（计算属性）和方法：makeNoise()
        {
            var hasBasket = false
        }
        class Tandem: Bicycle                   //定义了Bicycle类的一个子类Tandem，同样继承了Bicycle的所有属性和方法，所以也继承了Bicycle所继承的Vehicle的所有属性和方法
        {
            var currentNumberOfPassengers = 0
        }
        用点.操作符来访问属性、方法，包括继承的属性和方法
    3.覆盖
        子类可以覆盖从父类继承而来的同名的实体的方法、类型方法、属性、下标，在同名的这些东西前加override 关键字，表示覆盖掉父类继承而来的同名的方法、属性、下标
        Swift将在编译时检查override后的方法、属性、下标在父类中是否有同名的方法属性下标，如果没有，将产生编译时错误
        3.1访问父类中的同名方法、属性、下标
            有时需要在子类的覆盖方法、属性、下标中访问父类的某些操作，可以在覆盖的方法、属性、下标中使用：super.函数名 的方式来调用父类中的同名操作
            如：在子类中有个override someMethod()方法，可以在函数体内通过：super.someMethod()来调用父类中的someMethod()方法
            在子类中的overrride someProperty可以在其getter和setter方法内通过super.Property来调用父类中的setter和getter方法
            子类中有个override someIndex可以通过super[someIndex]调用父类中的下标
        3.2覆盖方法
        3.3覆盖属性
            注意，当你覆盖了一个属性，并重写了setter方法时，也必须提供新的getter方法，如果getter方法与父类中的getter一致，可以用super.来直接调用父类的getter方法
            class Car: Vehicle  //定义了Vehicle父类的一个子类Car
            {
                var gear = 1                        //Car子类拥有一个新存储属性gear，并初始化为1
                override var description: String    //Car子类覆盖了父类的description属性，并在属性内调用了父类属性的操作
                {
                    return super.description + " in gear \(gear)"
                }
            }
        3.4覆盖属性观察器
            可以使用覆盖属性的方法来给从父类继承而来的属性添加属性观察器，属性观察器可以在继承而来的属性发生改变时执行相应操作
            不可以对继承来的常数属性或只读的计算属性添加属性观察器
            不可以对一个重写了setter方法的属性同时添加属性观察器，因为可以直接在setter里面对这个覆盖的新属性进行操作
            class AutomaticCar: Car 
            {
                override var currentSpeed: Double       //覆盖了Car父类中的currentSpeed属性（Car父类的currentSpeed属性是从Vehicle类继承而来），并对其添加属性观察器来修改gear的值
                {
                    didSet 
                    {
                        gear = Int(currentSpeed / 10.0) + 1
                    }
                }
            }
        3.5禁止覆盖
            可以在方法、属性、下标名前加final关键字，来防止他们在子类中被覆盖，如果发生了覆盖，会产生编译时错误
            可以在类名前使用final关键字，表示这个类不可被继承，如果发生了继承，会产生编译时错误

十二、初始化
    1.对存储属性初始化
        类和结构体必须给其中的所有存储属性赋初始值，可以通过构造函数和在定义时就直接赋值的方法对其进行初始化
        1.1构造函数
            构造函数在定义一个新实体时被调用，构造函数的最简形式是一个没有参数的方法，如：init(){}
            struct Fahrenheit 
            {
                var temperature: Double
                init()                  //结构体Fahrenheit包含了一个构造函数，这个构造函数对temperature存储属性初始化赋值
                {
                    temperature = 32.0
                }
            }
            var f = Fahrenheit()
            print("The default temperature is \(f.temperature)° Fahrenheit")
            //输出： The default temperature is 32.0° Fahrenheit
        1.2初始值法
            直接在定义时就赋初始值，效果与写在构造函数内相同，但是直接赋值在继承时简化了继承后的子类的构造函数
            如上例可以写成：
            struct Fahrenheit 
            {
                var temperature = 32.0
            }
    2.自定义初始化
        2.1初始化参数
            可以在构造函数中加入参数，在定义新实体时，这个构造函数被调用，实际参数的值传递给构造函数的形式参数
            构造函数的参数的用法与一般函数相同
            struct Celsius                                          //Celsius结构体包含两个构造函数，形参别名不同
            {
                var temperatureInCelsius: Double
                init(fromFahrenheit fahrenheit: Double) 
                {
                    temperatureInCelsius = (fahrenheit - 32.0) / 1.8
                }
                init(fromKelvin kelvin: Double) 
                {
                    temperatureInCelsius = kelvin - 273.15
                }
            }
            let boilingPointOfWater = Celsius(fromFahrenheit: 212.0)//定义一个新实体时根据形参别名来调用Celsius结构体内不同的构造函数
            let freezingPointOfWater = Celsius(fromKelvin: 273.15)
            2.1.1构造函数的形参别名
                由于一个结构体或类可以存在多个构造函数，而构造函数的名字都是init，所以需要通过使用形参别名来区分调用不同的构造函数
                可以在定义构造函数时省略形参别名，而在调用构造函数时使用构造函数的形参名
                不可以同时省略定义构造函数时的形参别名和调用构造函数时的形参名，这样会产生编译时错误，但是可以用下划线_代替形参别名，表明可以在调用时省略形参名，如：
                struct Celsius 
                {
                    var temperatureInCelsius: Double
                    init(fromFahrenheit fahrenheit: Double) 
                    {
                        temperatureInCelsius = (fahrenheit - 32.0) / 1.8
                    }
                    init(fromKelvin kelvin: Double) 
                    {
                        temperatureInCelsius = kelvin - 273.15
                    }
                    init(_ celsius: Double)                             //这个构造函数用下划线_代替形参别名
                    {
                        temperatureInCelsius = celsius
                    }
                }
                let bodyTemperature = Celsius(37.0) //调用构造函数没有形参名，所以调用有下划线_代替形参别名的那个构造函数
        2.2可选类型属性
            如果一个存储属性在定义结构体或类的一个实体时没有取值，可以将其定义为可选类型
            可选类型在初始化时自动初始化为nil
            可选类型的定义已经在上文提到过，格式为：变量名: 类型?
        2.3常量的初始化
            常量必须在初始化时赋值，而且一旦赋值不可更改
            对于类，一个常量在继承他的子类中也不能被更改
    3.默认构造函数
        对于一个类，Swift自动生成一个构造函数，如果没有显式写构造函数，Swift实际上将直接赋值的那些值作为一个构造函数init(){...//}给整个类进行初始化
        对于一个结构体，Swift实际上自动给每个成员属性生成构造函数，最后在整个结构体中生成一个构造函数，成员属性的名字作为init()的参数，所以可以用init(成员变量名:)的方法来给结构体的实体初始化，也可以不显示写构造函数
    4.对值类型的构造函数的委托
        构造函数可以调用其他的构造函数来完成对实体的初始化，这称为构造函数的委托，这种方法可以避免代码的重复
        对于值类型（结构体和枚举类型），构造函数的委托通过调用其他结构体内定义的构造函数来完成
        struct Size 
        {
            var width = 0.0, height = 0.0
        }
        struct Point 
        {
            var x = 0.0, y = 0.0
        }
        struct Rect 
        {
            var origin = Point()
            var size = Size()
            init() {}
            init(origin: Point, size: Size) 
            {
                self.origin = origin
                self.size = size
            }
            init(center: Point, size: Size) 
            {
                let originX = center.x - (size.width / 2)
                let originY = center.y - (size.height / 2)
                self.init(origin: Point(x: originX, y: originY), size: size)    //在Rect结构体中引用自己的init，相当于调用Rect内相应的构造函数来完成这个复杂的构造函数的初始化操作
            }
        }
        let basicRect=Rect()    //这种初始化方式调用Rect结构体内没有参数的init()构造函数，这个构造函数分别调用Size和Point的构造函数
        let originRect = Rect(origin: Point(x: 2.0, y: 2.0),size: Size(width: 5.0, height: 5.0))    //这种方法与在结构体内不显式写出构造函数等效，分别给origin和size赋值，然后这个构造函数再调用Point和Size的隐式构造函数
        let centerRect = Rect(center: Point(x: 4.0, y: 4.0),size: Size(width: 3.0, height: 3.0))    //这种方法调用了第三个构造函数，这个构造函数调用结构体内的相应的构造函数来完成对origin和size的初始化
    5.类的继承与初始化
        一个类的所有存储属性都必须在初始化时赋初始值，Swift提供了两种构造函数来确保所有存储属性都被初始化
        5.1指定构造函数和方便构造函数
            指定构造函数是类的主要构造函数，指定构造函数将一个子类所有新引进的存储属性初始化，并调用父类的相应的构造函数来完成继承而来的属性的初始化
            每个类都必须有至少一个指定构造函数
            方便构造函数是类的辅助性构造函数，可以定义一个方便构造函数来调用主要构造函数并设置不同参数，也可以定义一个方便构造函数来创建一个有特殊用途的类的实体
            5.1.1指定构造函数的语法
                与对于值类型（结构体、枚举类型）的构造函数格式相同：
                init(参数)
                {
                    语句
                }    
            5.1.2方便构造函数的语法
                在init关键字前加convenience关键字：
                convenicence init(参数)
                {
                    语句
                }
        5.2类的构造函数的委托
            Swift对构造函数的委托有以下3条规定：
                一个指定构造函数必须调用其直接继承的父类的一个指定构造函数（指定构造函数必须向上委托）
                一个方便构造函数必须调用同一个类的另一个构造函数
                一个方便构造函数必须最终调用一个指定构造函数（方便构造函数必须横向委托）
        5.3二相初始化
            类的初始化分为两个步骤，第一步，所有新引进的存储属性由所引进他们的类完成赋初始值的操作
            第二步，在新实体定义完成前，每个类有机会来修改这些存储属性
            二相初始化能防止存储属性在初始化前就被访问，也能防止存储属性被另一个构造函数赋了不同的值
            Swift编译器会执行四个步骤来确保二相初始化完成无误：
                一个指定构造函数必须确保在委托父类的构造函数前，这个类新引进的存储属性都被初始化
                一个指定构造函数必须先委托父类的构造函数，才能对一个继承的属性赋值，如果不这样，新值会被父类的初始化过程覆盖
                一个方便构造函数必须先委托另一个构造函数，才能对任何属性赋值，如果不这样，新值会被一个指定构造函数覆盖
                一个构造函数不能调用任何实体的方法、不能访问一个实体的属性、不能在第一个初始化步骤完成前用self关键字引用自己
            5.3.1二相初始化的步骤
                第一相：
                    1.一个指定构造函数或方便构造函数被调用
                    2.内存分配给这个类内的新实体，但是内存未被初始化
                    3.这个类的一个指定构造函数确保这个类新引进的属性都分配了内存，并有一个值，所以这些属性的内存被初始化
                    4.这个指定构造函数委托父类的构造函数，执行3中的操作
                    5.3与4步随着继承链一次执行，直到基类
                    6.到达基类之后，这个类的所有属性均已分配内存并赋值，所以这个类的实体已经被完全初始化，内存已经完全初始化，第一相完成
                第二相：
                    1.从基类开始，每个指定构造函数可以选择修改所在类新引进的属性，构造函数现在可以用self关键字引用自己所在的类
                    2.最后，所有的方便构造函数可以修改自己所在类新引进的属性，可以用self关键字引用自己所在的类
        5.4构造函数的继承和覆盖
            Swift中的子类不会从父类继承构造函数
            如果在子类中的构造函数与父类中的某个指定构造函数冲突，需要加override关键字
            如果在子类中的构造函数与父类中的某个方便构造函数冲突，由于父类的方便构造函数永远不会被子类调用（根据3条规定的规定1），所以不需要写override关键字
            class Vehicle 
            {
                var numberOfWheels = 0
                var description: String 
                {
                    return "\(numberOfWheels) wheel(s)"
                }
            }//Vehicle类给每一个存储属性都赋有初值，所以他自动产生一个默认构造函数init()，这个构造函数把初值赋给存储属性，而一个默认构造函数总是作为指定构造函数
            class Bicycle: Vehicle 
            {
                override init()     //Bicycle类继承Vehicle类，由于这个构造函数同样名为init()同样没有参数，所以需要用override关键字
                {
                    super.init()        //由于规定1，这里需要调用Vehicle类的指定构造函数，来先完成Vehicle类的初始化，才能在下面修改其内容
                    numberOfWheels = 2  
                }
            }
            如果一个子类的构造函数没有执行二相初始化的第二相操作，而且父类中有一个无参数的构造函数init()，则可以省略对父类构造函数的调用super.init()
            class Hoverboard: Vehicle   //Hoverboard类继承了Vehicle类
            {
                var color: String
                init(color: String) 
                {
                    self.color = color
                    //由于这个类的构造函数没有对父类的numberOfWheels进行修改，而且Vehicle父类有自动产生的init()构造函数，所以这里可以省略super.init()
                }
                override var description: String    //由于已经对Vehicle父类的description进行初始化，所以这里可以用override覆盖继承而来的description计算方法
                {
                    return "\(super.description) in a beautiful \(color)"
                }
            }
            子类在任何情况下都不可以修改从父类继承而来的常量
            5.4.1构造函数的自动继承
                如果在子类中所有新引进的属性都赋了初值，则有以下两条规定：
                    如果子类没有定义指定构造函数，他会自动继承所有父类的指定构造函数
                    如果子类继承了所有父类的指定构造函数，无论是通过上一条规定继承的，还是通过自定义初始化的方式在方便构造函数中委托，那么所有父类的方便构造函数也会被继承
                class Food 
                {
                    var name: String
                    init(name: String)  //这是一个指定构造函数，因为在这个构造函数中给这个类的所有存储属性赋了值
                    {
                        self.name = name
                    }
                    convenience init()  //这是一个方便构造函数，他委托这个类的指定构造函数，并将一个参数值传递给指定构造函数
                    {
                        self.init(name: "[Unnamed]")
                    }
                }
                let namedMeat = Food(name: "Bacon") //这个实体的初始化调用了指定构造函数init(name: String)
                let mysteryMeat = Food()            //这个实体的初始化调用了方便构造函数init()，这个方便构造函数将"[Unnamed]"作为参数传递给指定构造函数init(name: String)，并委托他进行初始化
                class RecipeIngredient: Food 
                {
                    var quantity: Int               //RecipeIngredient类继承Food类，并新引入了quantity属性
                    init(name: String, quantity: Int) 
                    {
                        self.quantity = quantity
                        super.init(name: name)
                    }
                    override convenience init(name: String) 
                    {
                        self.init(name: name, quantity: 1)
                    }
                }

CoreGraphics
    使用CoreGraphics来绘制低级的2D图形
一、几何数据类型
    1.struct CGFloat
        是一种浮点类型，其精度根据所要编译的目标平台的CPU位数决定，如果是64位，等同于Double，如果是32位，等同于Float
        1.1方法
            1.1.1func addingProduct(_ lhs: CGFloat, _ rhs: CGFloat) ->CGFloat
                返回一个CGFloat类型，值为两个CGFloat类型参数的和

    2.struct CGPoint
        一种代表一个点的两个坐标的结构体
    3.struct CGSize
        一种包含了宽度、长度值的结构体
    4.struct CGRect
        代表了一个包含了位置和维度的矩形的结构体
    5.struct CGVector
        一种二维向量结构体
    6.struct CGAffineTransform
        一种代表仿射变换矩阵的结构体，用来绘制二维图形
        仿射变换是一个向量空间进行线性变换和平移
        一个仿射变换矩阵是3*3矩阵，[[a,b,0],[c,d,0],[tx,ty,1]]，由于第三列永远是[0,0,1]，所以CGAffineTransform只包含前两列数据
二、二维绘图
    1.class CGContext
        一个二维绘图环境
        1.1绘制图形
            1.1.1func clear(_ rect: CGRect)
                绘制一个透明矩形
            1.1.2func fill(_ rect: CGRect)
                在当前绘图状态定义的填充颜色下填充一个矩形区域
            1.1.3

@discardableResult->?

*/

//T9 Button clicking example
import UIKit
class ViewController: UIViewController
{
    @IBOutlet weak var xxLable: UILabel!    //Outlet is a reference to the item. Differ from Action. 
                                            //weak means you can break reference when needed.
                                            //! means not to check it's null.
                                            //var means variable.
                                            //xxLable: name of variable
    @IBAction func buttonPressed(sender:UIButton) -> Type 
    {
        let title=sender.titleForState(.Normal)!    //let means constant
        xxLable.text="You clicked the \(title) button"
    }
}

//T14 First responder example
import UIKit
class ViewController: UIViewController
{
    @IBOutlet weak var email:UITextField!           //a simple login screen with email and passwd text field
    @IBOutlet weak var password:UITextField!
    @IBAction func buttonPressed(sender:UIButton)   //user click the login button
    {
        self.email.resignFirstResponder()           //release the first responder of the text field
        self.password.resignFirstResponder()        //hide the software keyboard
    }
    override func touchesBegan(touches: NSSet, withEvent event:UIEvent)
    {
        self.view.endEditing(true)                  //all the view release the first responder
    }
}

//T15 A slider and Label example
import UIKit
class ViewController:UIViewController
{
    @IBOutlet weak var label: UILabel!
    @IBAction func sliderchanged(sender: UISlider)  //the function called when slider value is changed
    {
        var sliderValue=lroundf(sender.value)       //the value of slider is a float, lroundf(float)returns the integer
        label.text="\(sliderValue)"                 //the text label shouws the integer of the slider value
    }
}

//T16 A UISegment Control and Label example
import UIKit
class ViewController:UIViewController
{
    @IBOutlet weak var label: UILabel!
    @IBAction func toggle(sender: UISegmentedControl)//the function called when the UIsegment is clicked
    {
        if sender.selectedSegmentIndex==0           //the segment index starts from 0 to [count-1]
            label.text="Private"                    //click the Private segment, the label text shows "Private"
        else
            label.text="Public"
    }
}

//T20 Table views with same content in all cells
import UIKit
class ViewController: UIViewController, UITableViewDataSource
{
    func numberOfSectionsInTableView(tableView: UITableView) ->Int
    {
        return 1                                                    //how many sections in the table
    }
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) ->Int
    {
        return 3                                                    //how many rows in the table
    }
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell
    {
        var cell= UITableViewCell()                                 //a variable defining the cell
        cell.textLabel?.text="xxx"                                  //? will check whether the table is expty
                                                                    //the content is "xxx"
        return cell
    }
}

//T21 Table views with contents from a table view source
import UIKit
class ViewController: UIViewController, UITableViewDataSource
{
    let people=[("Bucky Roberts"),("Lisa Tucker"),("Emma Hotpocket")]
    func numberOfSectionsInTableView(tableView: UITableView) ->Int
    {
        return 1                                                    //how many sections in the table
    }
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) ->Int
    {
        return people.count                                         //rows=the count of people
    }
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell
    {
        var cell= UITableViewCell()                                 //a variable defining the cell
        var personName=people[indexPath]                            //the content of current row comes from the index of people
        cell.textLabel?.text=personName                             
        return cell
    }
}