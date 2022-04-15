# **Machi Engine**
[![Machi-Build](https://github.com/fabyday/Machi-Engine/actions/workflows/machi-build.yml/badge.svg?branch=dev1)](https://github.com/fabyday/Machi-Engine/actions/workflows/machi-build.yml)

**Machi** is c++ game engine.   
this is one of my hobby project.  
it is strongly inspired by **Unreal Engine**.

# **Plan**
- first plan is making **Window** version Engine. I need to concern compatibility with other OS Apis.  
- making **Engine Editor** is second objective. 


# **Supported OS Platform**
**Windows 10**
- **DirectX12**


**MacOS**(will support soon)
- **Metal**


# **Version**
current branch :  dev.1

## **Branch Naming**
- **master** : Program operation is ___guaranteed___.
- **dev**__.x__ :  temporary development branch. Program operation is ___not guaranteed___.




# **Dependency**
- cmake
- directx12(windows only)
- metal(Mac Only)
- spdlog
- imgui



# **Directory**
```
/cmakes # build helper directory (cmake module directory)
/Engine #Engine Core directory
    /Core # Engine Core Directory
    /Editor # Engine GUI Editor
    /ThirdParty # ThirdParty Library Directory
/Test #Test program directory
```