class std
{
    static cout($arg)
    {
        Write-Host($arg)
    }
}

foreach ($item in Get-Content -Path ./test.ps1) 
{
    Write-Host($item)
}