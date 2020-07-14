class Base 
{
    [int]$a
    Base([int]$num)
    {
        $this.a = $num
    }
}
class Derived 
{
    Derived():Base(100) {} 
}