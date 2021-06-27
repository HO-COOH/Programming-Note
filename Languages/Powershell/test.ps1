using namespace System;
$list = [Collections.Generic.List[int]]::new();

for ($i = 0; $i -lt 5; $i++) 
{
    $list.Add($i);
}

# $list.ForEach({param ($v) 
#     [Console]::WriteLine($v);
# });

"Hello World".Split(' ').ForEach({[Console]::WriteLine($_)});