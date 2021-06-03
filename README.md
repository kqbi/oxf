# oxf
IBM Rational Rhapsody oxf状态机，增加c++11智能指针版本c11分支

win：
  切换master分支，此分支为IBM的win原版
  用virtual studio打开oxf文件夹下的oxf.dsp即可  
linux：
 切换linux分支，此分支为IBM的linux原版
 切换到Share/LangCPP下使用 make -f linuxbuild.mak
 
c11：
  切换c11分支，使用CMakeLists.txt并依赖boost，附带简单例子，供参考

no-boost:
  切换no-boost分支,增加纯c++版本(去除c11分支的boost依赖) 线程及超时控制取自https://github.com/xia-chu/ZLToolKit
  
golang版：https://github.com/kqbi/go-oxf.git
