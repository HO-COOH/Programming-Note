# A simple html document
```html
<!DOCTYPE html>
<html>
<head>
    <title>Page Title</title>
</head>
<body>

    <h1>My First Heading</h1>
    <p>My first paragraph.</p>
    <p>This is another paragraph.</p>
</body>
</html>
```

The ``<!DOCTYPE html>`` declaration defines this document to be HTML5  
The ``<html>`` element is the root element of an HTML page  
The ``<head>`` element contains meta information about the document  
The ``<title>`` element specifies a title for the document  
The ``<body>`` element contains the visible page content  
The ``<h1>`` element defines a large heading  
The ``<p>`` element defines a paragraph  
HTML tags are element names surrounded by angle brackets:
```html
<tagname>contents here</tagname>
```
**Only the content inside <body> section is displayed.**

## HTML Documents
All Html documents must start with a document type declaration:
```html
<!DOCTYPE html>
```
The document itself begins with ``<html>`` and ``</html>``. The visible part is between ``<body>`` and ``</body>``.

## Head
``<head>`` element is a container for metadata, the data about the HTML document. Metadata is not displayed. Also, internal style CSS is defined here, enclosed by ``<style>CSS here</style>``. External style CSS is declared by a ``<link rel= "stylesheet" href="external.css">`` tag. 
```html
<head>
    <title>someTitle</title>
    <meta charset="UTF-8">
    <style>Internal style CSS here</style>
    <link rel="stylesheet" href="external.css">
</head>
```

## Headings
Html headins are defined with ``<h1>`` to ``<h6>`` tags, while:
- ``<h1>`` defines the most important heading.
- ``<h6>`` defines the least important heading.
Each level heading has a default size, to overwrite it, use ``style`` attribute and ``font-size`` property.
```html
<h1 style="font-size:60px">someHeading</h1>
```

## Paragraphs
Defined with ``<p>`` tag. The browser will remove any extra spaces and extra lines within the ``<p>`` tags. When you need to insert a line break, add ``<br>``. ``<br>`` tag does not has an ending tag.  
Use ``<pre>`` tag for preformatted text, so that extra spaces **will not** be removed.

## Links
Defined with ``<a>`` tag. The link's destination is specified with ``href`` attribute.
```html
<a href="link here">This is a link</a>
```
To specify how the new page is opened, use ``target`` attribute:
- ``_blank`` - Opens in new window
- ``_self`` - Open in the current context (**default**)(maybe in a frame)
- ``_parent`` - Open in the parent frame (if not in a frame, same as ``_top``)
- ``_top`` - Open in the current window, with a new frame    

## Images
Defined with ``<img>`` tag. Attributes:
- source file: ``src``
- alternative text: ``alt``(if error / screen reader is used)
- ``width``
- ``height``
- ``style``: can be used to specify ``width`` and ``height``
  ```html
  <img src="someImage.img" style="width:128px; height:128px">
  ```
  use ``float`` attribute to inline a image to the left or right to the text
  ```html
  <p>
      <img src="someImage.img" style="float:left; width:...">
      someText in this paragraph
  </p>
  ```
Images can be used as a link.
```html
<a href="someLink">
    <img src="some.img" alt="text">
</a>
```

## Buttons
Defined with ``<botton>`` tag.
Button can be used as a link. Need Javascript.

## Tables
Defined with ``<table>`` tag.
- Add a caption to a table, use ``<caption>`` tag.
- Header row is defined with the ``<th>`` tag.
- Each row is defined with ``<tr>`` tag.
- Each cell in the row is defined with ``<td>`` tag.
Tables are displayed without borders by default. To add border, use ``border`` property.  
- To make a cell span >1 column, use ``colspan`` attribute.
- To make a cell span >1 row, use ``rowspan`` attribute.
```html
<th colspan="2">someHeading</th>
```

## Lists
- Unordered/bullet lists are defined with ``<ul>`` tag
- Ordered/numbered list are defined with ``<ol>`` tag
followed by items defined by ``<li>`` tag
```html
<ul>
    <li>Coffee</li>
    <li>Tea</li>
    <li>Milk</li>
</ul>
```

## Iframe
An iframe is used to display a web page within a web page, defined by ``<iframe>`` tag.
- ``src`` - specify the URL of the inline frame page
- ``height``
- ``width``
- ``name`` - specify a name for the iframe, and then act as a target of a link

## Script
The ``<scirpt>`` tag is used to define a client-side Javascript. It either contains the code or points to an external code through ``src`` attribute.  
If the browser does not support Javascript or user disabled the feature, ``<noscript>`` tag can be used to provide alternative content.

## Special formating element
- ``<b>`` - Bold text
- ``<strong>`` - Important text
- ``<i>`` - Italic text
- ``<em>`` - Emphasized text
- ``<mark>`` - Marked text
- ``<small>`` - Small text
- ``<del>`` - Deleted text
- ``<ins>`` - Inserted text (appeared with an underscore)
- ``<sub>`` - Subscript text
- ``<sup>`` - Superscript text
- ``<q>`` - Short quotations (used with ``<p>``)
- ``<blockquote>`` - Long quotations (can be used independently)
- ``<abbr>`` - Abbreviations, appeared with a dot underscore 
- ``<address>`` - Contact information, usually displayed as italic
- ``<cite>`` - Title of a work, usually displayed as italic
- ``<bdo dir="rtl">`` - Override the current text direction, right->left
Browsers display ``<strong>`` as ``<b>`` and ``<em>`` as ``<i>``.

## Comments
Add comments to HTML source file by:
```html
<!-- Comments here -->
```

# Attributes
## href
## src
## width & height
## alt
``alt`` attribute specifies an alternative text to be used, if an image cannot be displayed.
## title
Similar to ``alt``, title provides additional "tool-tip" information, which will be displayed when hovering the mouse over it.
## style
Specify the styling of an element, like color, background-color, font-family, font-size, text-align, size. ``style`` attribute has the following syntax:
```html
<tagname style="property:value">
```
where ``property`` is a CSS property, and ``value`` is a CSS value.

### Color
- Using predefined color names:
```html
<h1 style="color:Tomato;">someHeading</h1>
```
- Using RGB value (and optional alpha channel):
```html
<p style="background-color:rgb(255,0,0);">someParagraph</p>
```
- Using hex value:
```html
<blockquote style="background-color:#ffff00;">
A programming language for Real Men. Most languages try to provide a simplified way to solve specific problems well. C++ makes no such concession and tries to be mediocre at everything. It lets you program at a very high level, and a very low level in the same program. It lets you write procedural code, object oriented code, generic code and mix them all up. It makes you decide everything and provides no help if you get it wrong.
</blockquote>
```
- Using HSL value (and optional alpha channel)
 - hue: red 0 -> green 120 -> blue 240 -> red 360
 - saturation: gray 0% -> full color 100%
 - lightness: black 0% -> white 100%
```html
<b style="color:hsl(0, 100%, 50%)">Don't try this at home!</b>
```
## class
``class`` attribute is used to define same style for the elements with the same class name.  
Elements can have more than one class name, seperated by a **space**
```html
<h2 class="city main">London</h2>
```
## id
``id`` attribute specifies a unique id for an element, which **must** be unique within the HTML document.  
Combining ``id`` and ``href`` to make a bookmark, which on click will jump to the location to the element with the referenced id.
```html
<p id="paragraph1">someContent</p>
<!-- ... -->
<a href="#paragraph1">Jump to paragraph1</a>
```
``href`` can even jump to another HTML document with the specified id.
```html
<a href="anotherPage.html#paragraph1">Jump to paragraph1</a>
```


class name can be used by Javascript. Accessing the elements by using ``document.getElementsByClassName()``
id can be used by Javascript. Accessing the element by using ``document.getElementById()``