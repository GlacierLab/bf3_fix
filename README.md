# bf3_fix
### 已被[此项目](https://github.com/Bartis1313/bf3-hudfix)取代  

解决战地3在高分辨率屏幕下的UI缩放问题
![4K](preview.png)


## 使用方法
1. clone本项目并构建 或 下载[Release](https://github.com/GlacierLab/bf3_fix/releases/tag/Prebuilt)中的预编译版本  
2. 重命名游戏目录下的`Engine.BuildInfo_Win32_Retail_dll`为`ori_Engine.BuildInfo_Win32_Retail_dll`  
3. 将构建好的`Engine.BuildInfo_Win32_Retail_dll`复制到游戏目录下  
4. 照常启动游戏  

## 构建环境
带有C++工作负载的VS2022  

## 原理
傻逼EA写死了UI缩放的最大分辨率是1280x720，所以大于这个分辨率都不会缩放UI  
这个项目通过动态修改内存，替换了判断1280x720到上限的逻辑，让UI缩放一直启用  
为什么必须是动态修改内存呢？因为游戏有加壳，我懒得脱壳了，还是DLL挂钩注入来的简单粗暴  
具体请参考[我写的文章](https://zhuanlan.zhihu.com/p/8621793244)  

## 缺陷
- 设置界面的部分文字会闪烁  
- 仅在单人模式下进行了测试，不保证对反作弊不产生影响，请自行考虑是否用于多人模式  

## 许可
MIT 或 [琴梨梨标准许可](https://zhuanlan.zhihu.com/p/7134329439)  

## 鸣谢
https://github.com/SeanPesce/DLL_Wrapper_Generator
