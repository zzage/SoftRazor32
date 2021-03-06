#pragma once

#ifndef _STDINT
#include <stdint.h>
#endif

#ifndef _INC_WINDOWS
#include <Windows.h>
#endif

#ifndef _OLEAUTO_H_
#include <OleAuto.h>
#endif

/*
    Reference From Semi VB Decompiler
    Thank: vbgamer45
    http://www.vbforums.com/member.php?51546-vbgamer45
*/

/*
    部分结构摘自:
    Thank: kenmark
    http://bbs.pediy.com/showthread.php?t=28715
    http://bbs.pediy.com/showthread.php?t=29307
*/
#ifndef _M_IX86
#error "The architecture does not support!"
#endif

#ifdef _WIN64
#error "不支持64位模式!"
#endif

#pragma pack(push, 1)

#define VBTF_APARTMOD         0x00000001          //指定多线程使用一个单元模型 (Apartment Model)
#define VBTF_REQUIRELIC       0x00000002          //指定做授权验证 (仅OCX文件) (Require License)
#define VBTF_UNATTENDED       0x00000004          //指定没有GUI的元素应该被初始化 (Unattended)
#define VBTF_SNGTHREAD        0x00000008          //指定映像是单线程的 (Single Threaded)
#define VBTF_RETAINED         0x00000010          //指定保留文件在内存中 (仅Unattended) (Retained)

typedef EXCEPTION_DISPOSITION (__cdecl * func_seh_except_handler) (
  struct _EXCEPTION_RECORD  * ExceptionRecord,
  void                      * EstablisherFrame,
  struct _CONTEXT           * ContextRecord,
  void                      * DispatcherContext);

typedef struct _EXCEPTION_REGISTRATION
{
  struct _EXCEPTION_REGISTRATION    * prevFrame;
  func_seh_except_handler             Handler;
} EXCEPTION_REGISTRATION, *LPEXCEPTION_REGISTRATION;


typedef EXCEPTION_DISPOSITION (__cdecl * func__vbaExceptHandler) (
  DWORD                       ExceptionCode, 
  LPEXCEPTION_REGISTRATION    ExceptionRegistration);

typedef struct _VB_PROC_TABLE_INFO
{
  uint32_t                data_00;
  uint32_t                Record;
  uint32_t                data_08;
  uint32_t                data_0C;
  uint32_t                data_10;
  uint32_t                Owner;
  uint32_t                rtl;
  uint32_t                data_1C;
  uint32_t                data_20;
  uint32_t                data_24;
  uint16_t                JmpCnt;
  uint16_t                data_2A;
  uint32_t                data_2C;
  uint32_t                data_30;
  uint32_t                ConstPool;
} VB_PROC_TABLE_INFO, VBPTI, *PVBPTI;

typedef struct _VB_PROC_DESC_INFO
{
  PVBPTI                  lpTableInfo;
  uint16_t                field_04;
  uint16_t                FrameSize;
  uint16_t                ProcSize;
  uint16_t                field_0A;
  uint16_t                field_0C;
  uint16_t                field_0E;
  uint16_t                field_10;
  uint16_t                field_12;
  uint16_t                field_14;
  uint16_t                field_16;
  uint16_t                field_18;
  uint16_t                field_1A;
  uint16_t                Flag;
} VB_PROC_DESC_INFO, VBPDI, *PVBPDI;

typedef const VBPDI * CPVBPDI;

typedef struct _VB_EVENT_POINTER    //事件指针?
{ //sizeof() = 0x0E
  uint8_t                   Const1;
  uint32_t                  Flag1;
  uint32_t                  Const2;
  uint8_t                   Const3;
  PVBPDI                    lpDescInfo;
} VB_EVENT_POINTER, VBEP, *PVB_EVENT_POINTER, *PVBEP, **PPVBEP;

typedef struct _VB_EVENT_TABLE    //事件处理程序表
{ //sizeof() = 0x18
  uint32_t                        dwNull;
  struct _VB_CONTROL            * lpControlType;        //指针指向控件类型
  struct _VB_OBJECT_INFO        * lpObjectInfo;         //指针指向对象信息
  LPVOID                          lpQueryInterface;     //跳转到 EVENT_SINK_QueryInterface
  LPVOID                          lpAddRef;             //跳转到 EVENT_SINK_AddRef
  LPVOID                          lpRelease;            //跳转到 EVENT_SINK_Release
//PVBEP                           lpEventPointer[lpControlType.EventCount]
} VB_EVENT_TABLE, VBET, *PVB_EVENT_TABLE, *PVBET;

typedef struct _VB_EVENT_LINK
{ //sizeof() = 0x0D
  uint16_t          Const1;
  uint8_t           CompileType;
  PVBET             pEvent;
  uint8_t           PushCmd;
  uint32_t          PushAddress;
  uint8_t           Const2;
} VB_EVENT_LINK, VBEL, *PVB_EVENT_LINK, *PVBEL;

//VB控件
typedef struct _VB_CONTROL
{ //sizeof() = 0x28  结构大小
  uint16_t          wFlagImplement;         //实现标志
  uint16_t          wEventHandlerCount;     //事件处理程序数量
  uint16_t          wFlagIndexRef;
  uint16_t          owEventsOffset;         //内存结构复制事件的偏移
  LPGUID            lpGuid;                 //控件GUID的指针
  uint32_t          dwIndex;                //控件的索引ID
  uint32_t          dwNull;
  uint32_t          dwNull2;
  PVBET             lpEventHandlerTable;    //指针指向事件处理程序表
  LPVOID            lpIdeData;              //仅用于IDE模式下
  PCHAR             lpszName;               //控件名称指针
  uint32_t          dwIndexCopy;            //此控件的辅助索引ID
} VB_CONTROL, VBCTRL, *PVB_CONTROL, *PVBCTRL;

//VB私有对象描述符
typedef struct _VB_PRIVATE_OBJECT_DESCRIPTOR
{ //sizeof() = 0x40
  LPVOID                                  lpHeapLink;
  struct _VB_OBJECT_INFO                * lpObjectInfo;
  uint32_t                                dwReserved;
  uint32_t                                dwIdeData;
  uint32_t                                dwUnknown;
  uint32_t                                dwUnknown2;
  struct _VB_PRIVATE_OBJECT_DESCRIPTOR  * lpObjectList;
  uint32_t                                dwIdeData2;
  struct _VB_PRIVATE_OBJECT_DESCRIPTOR  * lpObjectList2;
  uint32_t                                dwUnknown3;
  uint32_t                                dwUnknown4;
  uint32_t                                dwIdeData3;
  uint32_t                                dwUnknown5;
  uint32_t                                dwUnknown6;
  uint32_t                                dwObjectType;
  uint32_t                                dwIdentifier;
} VB_PRIVATE_OBJECT_DESCRIPTOR, VBPRIOBJDESCR, *PVB_PRI_OBJ_DESCR, *PVBPRIOBJ;

//VB公共对象描述符
typedef struct _VB_PUBLIC_OBJECT_DESCRIPTOR   //这个就是每个对象描述符的结构 
{ // sizeof() = 0x30
  struct _VB_OBJECT_INFO  * lpObjectInfo;               //VA 指向一个ObjectInfo_t类型,来显示这个OBJECT的数据
  uint32_t                  dwReserved;                 //保留未使用,编译后总为-1
  PSHORT                    lpPublicBytes;              //VA 指向外部可见变量表大小 (integers)
  PSHORT                    lpStaticBytes;              //VA 指向外部不可见变量表大小 (integers)
  LPVOID                    lpModulePublic;             //VA 指向外部可见变量表
  LPVOID                    lpModuleStatic;             //VA 指向外部不可见变量表
  PCHAR                     lpSZObjectName;             //VA 字符串,这个OBJECT的名字
  uint32_t                  dwMethodCount;              //events, funcs, subs(事件\函数\过程)数目
  PCHAR *                   lpMethodNamesArray;         //指向方法名称指针数组
  uint32_t                  oStaticVars;                //OFFSET  从pModuleStatic指向的静态变量表偏移
  uint32_t                  fObjectType;                //比较重要显示了这个OBJECT的实现,具体见下表
  uint32_t                  dwNull;                     //编译后无效
} VB_PUBLIC_OBJECT_DESCRIPTOR, VBPUBOBJDESCR, *PVB_PUB_OBJ_DESCR, *PVBPUBOBJ;

//VB可选对象信息
typedef struct _VB_OPTIONAL_OBJECT_INFO // 这个是可选的OBJECT_INFO和PEHEADER里的OPTIONAL_HEADER类似，是否有要看每个Object_t里面的ObjectTyper表里的倒数第二个位（详细看上表）
{ //sizeof() = 0x40
  uint16_t          wObjectGuids;                 //有多少GUID要注册,2=设计器
  uint16_t          wNull;
  LPGUID            lpObjectGuid;                 //对象唯一的GUID
  uint32_t          dwNull;                       //没有用的填充东西

  LPGUID          * lpUuidObjectGUI;              //指针指向对象接口GUID的数组
  uint16_t          wObjectControls;              //上面数组有多少GUID
  uint16_t          wNull2;

  PVBCTRL           lpControls2;                  //通常是一样的lpControls
  uint16_t          wObject;              //上面数组有多少GUID
  uint16_t          wNull3;

  LPGUID          * lpObjectGuid2;                //指针指向对象GUID的数组
  uint16_t          wControlCount;                //下面控件数组的数量
  uint16_t          wNull4;

  PVBCTRL           lpControls;                   //指向控件表
  uint16_t          wEventCount;                  //事件的个数,比较重要,知道有几个事件
  uint16_t          wPCodeCount;                  //此对象中PCode使用的数量
  uint16_t          owInitializeEvent;            //偏移,从aEventLinkTable指向初始化事件的偏移
  uint16_t          owTerminateEvent;             //偏移,从aEventLinkTable指向终止事件的偏移
  PVBEL             lpEventLinks;                 //指针指向EventLink的指针
  LPVOID            lpBasicClassObject;           //指针指向一个内存中的类对象
  uint32_t          dwNull3;                      //没有用的填充东西
  LPVOID            lpIdeData;                    //仅用于IDE模式下
} VB_OPTIONAL_OBJECT_INFO, VBOOI, *PVB_OPTIONAL_OBJECT_INFO, *PVBOOI;

//VB对象信息
typedef struct _VB_OBJECT_INFO //这个是显示这个OBJECT信息的结构,每一个OBJECT都有一个
{ //sizeof() = 0x38
  uint16_t                        wRefCount;
  uint16_t                        wObjectIndex;
  struct _VB_OBJECT_TABLE       * lpObjectTable;
  uint32_t                        lpIdeData;        //编译后总为0,仅用于IDE模式下
  PVBPRIOBJ                       lpPrivateObject;  //指向私有对象描述符,当它是一个模块,此值总为-1
  uint32_t                        dwReserved;
  uint32_t                        dwNull;
  PVBPUBOBJ                       lpPublicObject;   //反向指针指向公有对象描述符
  uint32_t                        lpProjectData;    //指向内存中的工程对象
  uint16_t                        wMethodCount;     //方法数量
  uint16_t                        wMethodCount2;    //编译后置零,仅用于IDE模式下
  LPDWORD                         lpMethods;        //指向方法表
  uint16_t                        wConstants;       //在常量池中的常量数量
  uint16_t                        wMaxConstants;    //常量在常量池中的分配
  uint32_t                        lpIdeData2;       //仅用于IDE模式下
  uint32_t                        lpIdeData3;       //仅用于IDE模式下
  LPVOID                          lpConstants;      //指针指向常量池
  /*
  !!可能存在可选对象信息
  if lpConstants points to the address after it, there's no optional object information
  如果lpConstants指向之后的地址，没有可选的对象的信息
  */
} VB_OBJECT_INFO, VBOI, *PVB_OBJECT_INFO, *PVBOI;

//VB对象表
typedef struct _VB_OBJECT_TABLE //这个是OBJECT 的总表，可以索引以后的每个OBJECT
{ //sizeof() = 0x54
  LPVOID          lpHeapLink;                             //没有用的填充东西
  LPVOID          lpExecProj;                             //指向VB工程Exec COM对象
  struct _VB_PROJECT_INFO2 * lpProjectInfo2;              //VA指向Project Info 2
  uint32_t        dwReserved;                             //编译后总为-1,未使用
  uint32_t        dwNull;                                 //编译后未使用
  LPVOID          lpProjectObject;                        //指向工程数据
  GUID            uuidObject;                             //对象表的GUID
  uint16_t        fCompileState;                          //在编译过程中使用的内部标志
  uint16_t        dwTotalObjects;                         //目前在工程总计对象数量
  uint16_t        dwCompiledObjects;                      //已编译对象数量
  uint16_t        dwObjectsInUse;                         //通常等于上面的编译后的对象数量
  PVBPUBOBJ       lpObjectArray;                          //VA指向第一个VB公共对象描述符,很重要
  uint32_t        fIdeFlag;                               //标志/指针,仅在IDE模式下使用
  uint32_t        lpIdeData;                              //标志/指针,仅在IDE模式下使用
  uint32_t        lpIdeData2;                             //标志/指针,仅在IDE模式下使用
  PCHAR           lpSZProjectName;                        //指向工程名字
  LCID            dwLcid;                                 //language ID1
  LCID            dwLcid2;                                //language ID2
  LPVOID          lpIdeData3;                             //标志/指针,仅在IDE模式下使用
  uint32_t        dwIdentifier;                           //结构的模板版本
} VB_OBJECT_TABLE, VBOBJTAB, *PVB_OBJECT_TABLE, *PVBOT;

//VB外部库
typedef struct _VB_EXTERNAL_LIBRARY
{
  uint32_t      lpLibraryName;         // VA 指向  NTS
  uint32_t      lpLibraryFunction;     // VA 指向  NTS
} VB_EXTERNAL_LIBRARY, VBEXLIB, *PVB_EXTERNAL_LIBRARY, *PVBEXLIB;

//VB外部表
typedef struct _VB_EXTERNAL_TABLE
{
  uint32_t      Flag;                 // 标志
  PVBEXLIB      lpExtLib;             // VA 指向ExternalLibrary结构的地址指针
} VB_EXTERNAL_TABLE, VBEXT, *PVB_EXTERNAL_TABLE, *PVBEXT;

//VB工程信息
typedef struct _VB_PROJECT_INFO 
{ //sizeof() = 0x23c
  union {
    char                      crSign[4];                  // 结构的签名特性,和魔术字符类似
    uint32_t                  dwSign;
  } Sign;

  PVBOT                       lpObjectTable;              // VA 结构指向的组件列表的地址指针（很重要的!（7.））  
  uint32_t                    dwNull;                     // 没有用的东西  
  PVOID                       lpCodeStart;                // VA 代码开始点,类似PEHEAD->EntryPoint这里告诉了VB代码实际的开始点  
  PVOID                       lpCodeEnd;                  // VA 代码结束点  
  uint32_t                    dwDataSize;                 // 标志1  
  PVOID                       lpThreadSpace;              // 多线程的空间??
  func__vbaExceptHandler      lpVBAExceptHandler;         // VA VBA异常处理器(SEH)地址指针  
  PVOID                       lpNativeCode;               // VA 本地机器码开始位置的地址指针  
  WCHAR                       szPathInformation[264];     // 原文件地址,一个字符串,长度最长为264
  PVBEXT                      lpExternalTable;            // VA 引用表的地址  
  uint32_t                    dwExternalCount;            // 引用表大小(个数)  
} VB_PROJECT_INFO, VBPI, *PVB_PROJECT_INFO, *PVBPI;

//VB工程信息2
typedef struct _VB_PROJECT_INFO2
{ //sizeof() = 0x28
  uint32_t              lpHeapLink;       //编译后未使用,总为0
  PVBOT                 lpObjectTable;    //回退指针
  uint32_t              dwReserved;       //保留未使用,编译后总为-1
  uint32_t              dwUnused;         //未使用
  PVB_PRI_OBJ_DESCR     lpObjectList;     //指向私有对象描述符指针数组
  uint32_t              dwUnused2;        //未使用
  PCHAR                 szProjDescr;      //szProjectDescription,指向工程描述符
  PCHAR                 szProjHelpFile;   //szProjectHelpFile,指向工程帮助文件
  uint32_t              dwReserved2;      //保留未使用,编译后总为-1
  uint32_t              dwHelpContextId;
} VB_PROJECT_INFO2, VBPI2, *PVB_PROJECT_INFO2, *PVBPI2;


//VB GUI表
typedef struct _VB_GUI_TABLE // sizeof() =  0x50
{
  uint32_t  lStructSize;       // 这个结构的总大小
  UUID      uuidObjectGUI;     // Object GUI的UUID
  uint32_t  Unknown1;          // ???????????????????????????????????
  uint32_t  Unknown2;          // ???????????????????????????????????
  uint32_t  Unknown3;          // ???????????????????????????????????
  uint32_t  Unknown4;          // ???????????????????????????????????
  uint32_t  lObjectID;         // 当前工程的组件ID
  uint32_t  Unknown5;          // ???????????????????????????????????
  uint32_t  fOLEMisc;          // OLEMisc标志
  UUID      uuidObject;        // 组件的UUID
  uint32_t  Unknown6;          // ???????????????????????????????????
  uint32_t  Unknown7;          // ???????????????????????????????????
  uint32_t  lpFormPointer;     // VA 指向GUI Object Info结构的地址指针
  uint32_t  Unknown8;          // ???????????????????????????????????
} VB_GUI_TABLE, VBGT, *PVB_GUI_TABLE, *PVBGT;

typedef struct _VB_EXTERNAL_COMPONENT
{
  uint32_t    dwStructLength;
  uint32_t    oUuid;
  uint32_t    dwUnknown;
  uint32_t    dwUnknown2;
  uint32_t    dwUnknown3;
  uint32_t    dwUnknown4;
  uint32_t    dwUnknown5;
  uint32_t    offsetGUID;
  uint32_t    lengthGUID;
  uint32_t    dwUnknown6;
  uint32_t    oFileName;
  uint32_t    oSource;
  uint32_t    oName;
} VB_EXTERNAL_COMPONENT, VBEXTCOMP, *PVB_EXTERNAL_COMPONENT, *PVBEXTCOMP;

//VB COM注册数据
typedef struct _VB_COM_REG_DATA // sizeof() = 0x30
{
  uint32_t  oRegInfo;                   //Offset 指向COM Interfaces Info结构（COM接口信息）
  uint32_t  oSZProjectName;             //Offset 指向Project/Typelib Name（工程名）
  uint32_t  oSZHelpDirectory;           //Offset 指向Help Directory（帮助文件目录）
  uint32_t  oSZProjectDescription;      //Offset 指向Project Description（工程描述）
  CLSID     uuidProjectClsId;           //Project/Typelib的CLSID
  LCID      dwTlbLcid;                  //Type Library的LCID
  uint16_t  wUnknown;                   //没有用的内存对齐空间1
  uint16_t  wTlbVerMajor;               //Typelib 主版本
  uint16_t  wTlbVerMinor;               //Typelib 次版本
  // ????
  uint16_t  wUnknown2;                  //没有用的内存对齐空间2
  uint32_t  dwUnknown;                  //没有用的内存对齐空间3
} VB_COM_REG_DATA, VBCRD, *PVB_COM_REG_DATA, *PVBCRD;

//VB COM注册信息
typedef struct _VB_COM_REG_INFO // sizeof() = 0x44
{
  uint32_t  oNextObject;            //Offset to COM Interfaces Info
  uint32_t  oObjectName;            //Offset to Object Name
  uint32_t  oObjectDescription;     //Offset to Object Description
  uint32_t  dwInstancing;           //Instancing Mode
  uint32_t  dwObjectId;             //Current Object ID in the Project
  CLSID     uuidObject;             //CLSID of Object
  uint32_t  fIsInterface;           // Specifies if the next CLSID is valid
  uint32_t  bUuidObjectIFace;       // Offset to CLSID of Object Interface
  uint32_t  bUuidEventsIFace;       // Offset to CLSID of Events(Controls) Interface
  uint32_t  fHasEvents;             // Specifies if the CLSID above is valid
  OLEMISC   dwMiscStatus;           // OLEMISC Flags (see MSDN docs)
  uint8_t   fClassType;             // Class Type
  uint8_t   fObjectType;            // Flag identifying the Object Type
  uint16_t  wToolboxBitmap32;       // Control Bitmap ID in Toolbox
  uint16_t  wDefaultIcon;           // Minimized Icon of Control Window
  uint16_t  fIsDesigner;            // Specifies whether this is a Designer
  uint32_t  oDesignerData;          // Offset to Designer Data
} VB_COM_REG_INFO, VBCRI, *PVB_COM_REG_INFO, *PVBCRI;

//VB 初始化头部结构
typedef struct _VB_HEADER
{
  union {
    char        crSign[4];    // 四个字节的签名符号，和PEHEADER里的那个signature是类似性质的东西，VB文件都是"VB5!"
    uint32_t    dwSign;
  } Sign;

  uint16_t      wRuntimeBuild;          // 运行时创立的变量（类似编译的时间）
  char          szLangDll[14];          // 语言DLL文件的名字（如果是0x2A的话就代表是空或者是默认的）
  char          szSecLangDll[14];       // 备份DLL语言文件的名字（如果是0x7F的话就代表是空或者是默认的，改变这个值堆EXE文件的运行没有作用）
  uint16_t      wRuntimeRevision;       // 运行时DLL文件的版本
  LCID          dwLCID;                 // 语言的ID
  LCID          dwSecLCID;              // 备份语言的ID（只有当语言ID存在时它才存在）
  PVOID         lpSubMain;              // VA sub main过程的地址指针（3.）（如果是0则代表这个EXE时从Form窗体文件开始运行的）
  PVBPI         lpProjInfo;             // VA 工程信息的地址指针，指向一个VB_PROJECT_INFO结构（2.）
  uint32_t      fMdlIntCtls;            // ?详细见"MDL 内部组建的标志表"
  uint32_t      fMdlIntCtls2;           // ?详细见"MDL 内部组建的标志表"
  uint32_t      dwThreadFlags;          // 线程的标志
  uint32_t      dwThreadCount;          // 线程个数
  uint16_t      wFormCount;             // 窗体个数
  uint16_t      wExtComponentCount;     // VA 外部引用个数例如WINSOCK组件的引用
  uint32_t      dwThunkCount;           // ?大概是内存对齐相关的东西
  PVBGT         lpGuiTable;             // VA GUI元素表的地址指针（指向一个GUITable_t结构（4.四））
  PVBEXTCOMP    lpExtComponentTable;    // VA 外部引用表的地址指针
  PVBCRD        lpComRegData;           // VA COM注册数据的地址指针
  uint32_t      oSZProjectDescription;  // Offset 指向工程EXE名字的字符串
  uint32_t      oSZProjectExeName;      // Offset 指向工程标题的字符串
  uint32_t      oSZProjectHelpFile;     // Offset 指向帮助文件的字符串
  uint32_t      oSZProjectName;         // Offset 指向工程名的字符串
} VB_HEADER, VBHDR, *PVB_HEADER, *PVBHDR;

/* other */
union PIFLAG
{
  uint8_t          Byte[4];
  uint16_t         Word[2];
  uint32_t         DWord;
};

#pragma pack(pop)

//* 线程标记的定义（ThreadFlags数值的含义）
//+-------+----------------+--------------------------------------------------------+
//| 值    | 名字           | 描述                                                   |
//+-------+----------------+--------------------------------------------------------+
//|  0x01 | ApartmentModel | 特别化的多线程使用一个分开的模型                        |
//|  0x02 | RequireLicense | 特别化需要进行认证(只对OCX)                             |
//|  0x04 | Unattended     | 特别化的没有GUI图形界面的元素需要初始化                |
//|  0x08 | SingleThreaded | 特别化的静态区时单线程的                                |
//|  0x10 | Retained       | 特别化的将文件保存在内存中(只对Unattended)               |
//+-------+----------------+--------------------------------------------------------+
//ex: 如果是0x15就表示是一个既有多线程,内存常驻,并且没有GUI元素要初始化

//* MDL 内部组建的标志表
//+---------+------------+---------------+
//|   ID    |    值      | 组建名称      |
//+---------+------------+---------------+
//|                           第一个标志 |
//+---------+------------+---------------+
//|    0x00 | 0x00000001 | PictureBox    |
//|    0x01 | 0x00000002 | Label         |
//|    0x02 | 0x00000004 | TextBox       |
//|    0x03 | 0x00000008 | Frame         |
//|    0x04 | 0x00000010 | CommandButton |
//|    0x05 | 0x00000020 | CheckBox      |
//|    0x06 | 0x00000040 | OptionButton  |
//|    0x07 | 0x00000080 | ComboBox      |
//|    0x08 | 0x00000100 | ListBox       |
//|    0x09 | 0x00000200 | HScrollBar    |
//|    0x0A | 0x00000400 | VScrollBar    |
//|    0x0B | 0x00000800 | Timer         |
//|    0x0C | 0x00001000 | Print         |
//|    0x0D | 0x00002000 | Form          |
//|    0x0E | 0x00004000 | Screen        |
//|    0x0F | 0x00008000 | Clipboard     |
//|    0x10 | 0x00010000 | Drive         |
//|    0x11 | 0x00020000 | Dir           |
//|    0x12 | 0x00040000 | FileListBox   |
//|    0x13 | 0x00080000 | Menu          |
//|    0x14 | 0x00100000 | MDIForm       |
//|    0x15 | 0x00200000 | App           |
//|    0x16 | 0x00400000 | Shape         |
//|    0x17 | 0x00800000 | Line          |
//|    0x18 | 0x01000000 | Image         |
//|    0x19 | 0x02000000 | Unsupported   |
//|    0x1A | 0x04000000 | Unsupported   |
//|    0x1B | 0x08000000 | Unsupported   |
//|    0x1C | 0x10000000 | Unsupported   |
//|    0x1D | 0x20000000 | Unsupported   |
//|    0x1E | 0x40000000 | Unsupported   |
//|    0x1F | 0x80000000 | Unsupported   |
//+---------+------------+---------------+
//|                          第二个标志  |
//+---------+------------+---------------+
//|    0x20 | 0x00000001 | Unsupported   |
//|    0x21 | 0x00000002 | Unsupported   |
//|    0x22 | 0x00000004 | Unsupported   |
//|    0x23 | 0x00000008 | Unsupported   |
//|    0x24 | 0x00000010 | Unsupported   |
//|    0x25 | 0x00000020 | DataQuery     |
//|    0x26 | 0x00000040 | OLE           |
//|    0x27 | 0x00000080 | Unsupported   |
//|    0x28 | 0x00000100 | UserControl   |
//|    0x29 | 0x00000200 | PropertyPage  |
//|    0x2A | 0x00000400 | Document      |
//|    0x2B | 0x00000800 | Unsupported   |
//+---------+------------+---------------+


//Object Type part of tCOMRegInfo//没有翻译的意义，就没有翻译，只是看看而已
//+-------+---------------+-------------------------------------------+
//| Value | Name          | Description                               |
//+-------+---------------+-------------------------------------------+
//|  0x02 | Designer      | A Visual Basic Designer for an Add.in     |
//|  0x10 | Class Module  | A Visual Basic Class                      |
//|  0x20 | User Control  | A Visual Basic ActiveX User Control (OCX) |
//|  0x80 | User Document | A Visual Basic User Document              |
//+-------+---------------+-------------------------------------------+


//Object_t.ObjectTyper 属性...//重要的属性表部分
//#########################################################
//form:              0000 0001 1000 0000 1000 0011 --> 18083
//                   0000 0001 1000 0000 1010 0011 --> 180A3
//                   0000 0001 1000 0000 1100 0011 --> 180C3
//module:            0000 0001 1000 0000 0000 0001 --> 18001
//                   0000 0001 1000 0000 0010 0001 --> 18021
//class:             0001 0001 1000 0000 0000 0011 --> 118003
//                   0001 0011 1000 0000 0000 0011 --> 138003
//                   0000 0001 1000 0000 0010 0011 --> 18023
//                   0000 0001 1000 1000 0000 0011 --> 18803
//                   0001 0001 1000 1000 0000 0011 --> 118803
//usercontrol:       0001 1101 1010 0000 0000 0011 --> 1DA003
//                   0001 1101 1010 0000 0010 0011 --> 1DA023
//                   0001 1101 1010 1000 0000 0011 --> 1DA803
//propertypage:      0001 0101 1000 0000 0000 0011 --> 158003
//                      | ||     |  |    | |    |
//[moog]                | ||     |  |    | |    |
//HasPublicInterface ---+ ||     |  |    | |    |  （有公用的接口）
//HasPublicEvents --------+|     |  |    | |    |  （有公用的事件）
//IsCreatable/Visible? ----+     |  |    | |    |  （是否可以创建，可见）
//Same as "HasPublicEvents" -----+  |    | |    |  
//[aLfa]                         |  |    | |    |
//usercontrol (1) ---------------+  |    | |    |  （用户控件）
//ocx/dll (1) ----------------------+    | |    |  （OCX/DLL）
//form (1) ------------------------------+ |    |  （是不是FORM是就是1）
//vb5 (1) ---------------------------------+    |  （是不是VB5是就是1）
//HasOptInfo (1) -------------------------------+  （有没有可选对象信息,有就是1,决定是不是指向OptionalObjectInfo_t类似与PEHEAD里的Optional信息一样）
//                                              |
//module(0) ------------------------------------+  （如果是Module模块就这里是0）