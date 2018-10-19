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