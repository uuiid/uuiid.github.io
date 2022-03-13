# win系统

## windwos的程序清单(manifest)
在win中, 程序清单可以指定win如何启动程序, 可以嵌入,也可以放在运行文件的旁边,
使用的是xml语言, 当然也可以用在dll中,
[msvc文档](https://docs.microsoft.com/zh-cn/windows/win32/sbscs/manifest-files-reference?redirectedfrom=MSDN)



## app utf-8

在windows中想要使用utf-8作为编译程序的启动环境，需要使用程序清单文件  
<details>
<summary>最简单的程序清单</summary>

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0">
    <application xmlns="urn:schemas-microsoft-com:asm.v3">
        <windowsSettings>
            <activeCodePage xmlns="http://schemas.microsoft.com/SMI/2019/WindowsSettings">UTF-8</activeCodePage>
        </windowsSettings>
    </application>
</assembly>
```

</details>
在这个程序清单中，我们只使用的一个项目，就是设置程序的运行环境为 utf-8 

## app 长路径
在使用wendows中，还有可能遇到超长路径的问题，这个时候也可以使用 windwos 的程序清单解决

<details>
<summary>utf-8和长路径一起启用</summary>

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0">
    <application xmlns="urn:schemas-microsoft-com:asm.v3">
        <windowsSettings>
            <longPathAware xmlns="http://schemas.microsoft.com/SMI/2016/WindowsSettings">true</longPathAware>
            <activeCodePage xmlns="http://schemas.microsoft.com/SMI/2019/WindowsSettings">UTF-8</activeCodePage>
        </windowsSettings>
    </application>
</assembly>
```

</details>  
在这个例子中，我们使用了程序清单，启用了utf-8和长路径