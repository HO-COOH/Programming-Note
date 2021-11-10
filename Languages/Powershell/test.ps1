using namespace System;
using namespace System.IO;
using namespace System.Diagnostics;

$counter = [PerformanceCounter]::new("Processor", "% Processor Time", "_Total", [Environment]::MachineName);
while ($true)
{
    [Console]::WriteLine($counter.NextValue());
    [System.Threading.Thread]::Sleep(1000);
}