$fileName="test.txt"
for($i=0; $i -le 4000; ++$i)
{
    # Write-Host($i)
    Out-File $fileName -Append -InputObject $i
}