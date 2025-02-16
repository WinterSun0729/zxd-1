# Project2说明

## 补充函数实现

在Graph.cpp中补充Index的get_string()函数实现如下:

```cpp
string In_box::get_string()
{
    Fl_Input& pi = reference_to<Fl_Input>(pw);
    const char* p = pi.value();
    string pt;
    while (*p != '\0')
    {
        pt.push_back(*p);
        p++;
    }
    return pt;
}
```

## 输入

例如 data.txt 文件位于 C:\MinGW\msys\1.0\home\Dong\program\p2 下

则 "File position:" 后输入 
```
C:\\MinGW\\msys\\1.0\\home\\Dong\\program\\p2\\data.txt
```
按照表格中日期格式

例如在date中输入9月10号

```
09-10
```

后点击确认按钮

