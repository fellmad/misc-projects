# https://learn.microsoft.com/en-us/powershell/scripting/learn/deep-dives/everything-about-exceptions?view=powershell-7.4

try {
    Write-Output('going to throw exception:')
    bogus-statement-that-will-throw-exception
}
catch {
    'exception happened:'
    Write-Output $_
}