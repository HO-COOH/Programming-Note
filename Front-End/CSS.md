# CSS
## Insert to HTML
```html
<head>
    <link rel="stylesheet" type="text/css" href="css_source.css">
</head>
```
```html
<head>
    <style>
        <!--css here -->
    </style>
</head>
```
## 语法
```css
selector {property:value;...}
```
### 复合选择器
- 包含元素用空格, ``div p`` 选中所有的div下的p，无论p是不是div所直接包含
- 直接后代用``>``, ``div > p``选中所有div直接包含的p
- 直接邻居用``+``, ``div + p``选中所有与div(后面)直接相邻的p
- 泛邻居用``~``, ``div ~ p``选中所有div(后面)的p
### selector
- simple selector: select elements based on ``tag-name``, ``id(#)``, ``class(.)``
- combinator selector
- universal selector ``*``
- grouping selector ``selector1, selector2 {...}``

## 通用属性
### 单位
#### 绝对单位
cm, mm, in（英尺）, px(1px=1/96 in，可能会因为高分辨率设备而改变)，pt（1pt=1/72 in），pc（1pc=12pt）
#### 相对单位
- em：相对于当前字体大小的倍数，1em=1倍于当前字体大小
- ch：相对于当前字体大小下数字0的宽度，比em小
- vw：1%的可视宽度
- vh：1%的可视高度
- vmin：1%的min（可视宽度，可视高度）
- vmax：1%的max（可视宽度，可视高度）
- %：其直接父元素的百分比大小


### Max-width
将元素设置``max-width`` 和 ``margin: auto`` 可以改善在窗口宽度小于max-width时的显示效果，浏览器会自动对超出宽度的元素移行
### Position
```css
position: static; /*所有HTML元素的默认position都是static，此时left right up down属性不起作用*/
position: relative; /*使用left right up down属性和默认位置来确定最终的位置*/
position: fixed;    /*位置不随滚动网页而变化，总是在原位*/
position: absolute; /*使用相对于这个元素的直接祖先的位置，如果没有，使用body作为直接祖先*/
position: sticky;   /*当元素到达相对位置时，表现为fixed，否则表现为absolute，与absolute的规则相同*/
```
### z-index
表示元素的层叠关系，``z-index: -1``表示底层

### Display
#### inline和block
inline不独占一行空间
block独占一行空间
#### 隐藏
隐藏一个元素通常有两种方法
- ``display: none;`` 使得这个元素消失，就好像没有在HTML文档中定义过一样
- ``display: hidden;`` 使得元素隐藏，但是还占据着元素之前的位置

### overflow
```css
overflow: visible;  /*超出的内容正常显示*/
overflow: hidden;   /*超出的内容不显示*/
overflow: scroll;   /*无论内容是否超出，总是显示滚动条，如果没有超出，滚动条为灰色不可滚动状态*/
overflow: auto;     /*内容超出才显示滚动条*/
/*细分水平和垂直方向*/
overflow-x:  
overflow-y:
```
### float
用于摆放元素在一个容器中的位置，例如：将一个图片放到文本的右边
```css
float: left;
float: right;
float: none;    /*默认值，位置按照在HTML中声明的顺序显示*/
float: inherit; /*继承其直接祖先的值*/
```
### opacity
范围从0-1，值越低，越透明
指定元素的子元素会继承父元素的opacity值，例如容器中的文字，可能也会变透明
可以使用RGBA的方法
```css
div {
    background: rgba(50,50,50,0.3)
}
```
### box-shadow
卡片的阴影效果：
```css
box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
```

## background
### image
```css
background-image: url("src.png");

background-repeat: repeat-x;    /*repeat horizontally*/
background-repeat: repeat-y;    /*repeat vertically*/
background-repeat: no-repeat;

background-position:

background-attachment: scroll;
background-attachment: fixed;
```

## Text
```CSS
text-align: center;
text-align: left;
text-align: right;

text-decoration: overline;      /*上划线*/
text-decoration: line-through;  /*中划线*/
text-decoration: underline;     /*下划线*/

text-transform: uppercase;  
text-transform: lowercase;
text-transform: capitalize; /*每个单词首字母大写*/

text-indent: 50px;      /*首行缩进的距离*/
letter-spacing： 3px;   /*字符间距*/
line-height: 0.8;       /*行距，默认值: 1.1-1.2*/
word-spacing: 10px;     /*单词间距*/
white-space: nowrap;    /*行截断，默认值: normal*/

text-shadow：2px 2px 5px red;   /*水平阴影，垂直阴影，模糊度，阴影颜色*/

font-family 用逗号分隔，如果字体名字由多个单词组成，用双引号括起来，最后一个字体应该是字体类型，作为当前面字体不可用时的备选(serif, sans-serif, monospace)
font-style: normal;
font-style: italic;
font-style: oblique;    /*类似于italic，不过更歪*/
font-weight: normal;
font-weight: bold;
font-variant: normal;
font-variant: small-caps;   /*所有小写字母转化为与原来同样高度的大写字母*/

font-size: 40px;    /*用户依然可以用缩放改变大小*/
font-size: 1ex;     /*1em是浏览器默认的字体大小就，通常为16px*/
font-size: 10vw;    /*字体大小随浏览器窗口改变，1vw是1%的浏览器窗口的可视宽度*/
```


## Link
一个link有4中状态：
- link: 未访问链接
- visited
- hover: 当鼠标悬浮在link上方
- active: 鼠标点击链接
可以用``linkName:status{}`` 的形式来分别装饰一个链接的不同状态
```css
display: inline-block;  /*将链接显示在一个方框内*/
```
## 伪类
语法：```element:pseudo-class-name``
如上面的link的4种状态实际上就是伪类，常见伪类：
- hover
- first-child：选中任何是第一个子元素的元素
- last-child:
- nth-child(n)
- lang(name)：选中``lang=“name”``的tag
- focus

## 伪元素
伪元素用来选中一个元素的一部分，语法：``element::pseudo-element``
常见伪元素：
- first-line
- first-letter
- before：用于在指定的element前插入一些内容
- after：用于在指定的element后插入一些内容
- selection：选中用户用光标选中的部分（比如修改高亮颜色）
## List
在HTML中：
- 无序列表<ul> 使用圆点标记
- 有序列表<ol> 使用数字或字母标记
列表也有默认的padding和margin
```css
/*list-style-type指定标记的符号*/
list-style-type: circle;
list-style-type: square;
list-style-type: upper-roman;   /*用于有序列表，使用大写罗马数字*/
list-style-type: lower-alpha;   /*使用小写英文字母*/

list-style-image: url("source.img");    /*使用图片作为标记*/

list-style-position: outside;   /*标记出现在列表外，与列表内容分离*/
list-style-position: inside;    /*标记出现在列表内，与列表内容合并*/
```
## Table
用``th``控制表头（表格的首行），用``td``控制单元格，用``tr:hover``控制当鼠标悬浮当前行的高亮颜色
用``tr:nth-child(even)``或``tr:nth-child(odd)``控制每行的属性（条带效果）

可以用``<div style="overflow-x:auto;">``将表格元素括起来，当表格过长时产生一个横向滚动条
```html
<div style="overflow-x:auto;">
    <table>
    <!-- table element here -->
    </table>
</div>
```