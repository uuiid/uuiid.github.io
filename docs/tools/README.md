# 记录一些好用的辅助工具

## cpp 工具

- vcpkg一个好用的c++包管理工具, **强烈推荐**
- chocolatey 包管理器, 安装软件的神器 [go](https://chocolatey.org/)
- vscode 代码编辑 ` choco install vscode `
- clion 也是代码编辑, 有一个就行 ` choco install clion-ide `
- notepad++ 文本编辑器, 用来替换 windows 的记事本好用太多 ` choco install notepadplusplus `
- wt window 的命令行对话框， 好用无比 ` winget install --id=Microsoft.WindowsTerminal -e `
- rapidee 环境变量编辑  ` choco install rapidee `
- sysinternals 系统工具包, **一定要有** ` choco install sysinternals `
- processhacker 好用无比的进程管理器 ` choco install processhacker `
- powertoys windows 启动器 ` choco install powertoys `
- cmake c++ 工程使用 ` choco install cmake ` 

## 一次性完成
``` PowerShell
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'));

choco install vscode clion notepadplusplus rapidee sysinternals processhacker powertoys cmake

```