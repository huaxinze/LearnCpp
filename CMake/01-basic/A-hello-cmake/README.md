1、cmake_minimum_required(VERSION <min>[...<max>] [FATAL_ERROR]) // 用于指定cmake的最低和最高版本，用于做版本控制cmake_minimum_required (VERSION 3.10.0...3.12.0)

2、project(<PROJECT-NAME>                           //用于指定cmake工程的名称 project (mytest)
    [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]] //用于指定cmake工程的版本号 project (mytest VERSION 1.2.3.4)
    [DESCRIPTION <project-description-string>]      //用于对工程的文本描述 project (mytest DESCRIPTION “This is mytest project.”)
    [HOMEPAGE_URL <url-string>]                     //用于指定工程的主页URL project (mytest HOMEPAGE_URL “https://www.XXX(示例).com”)
    [LANGUAGES <language-name>...]))                //用于选择构建工程需要的编程语言 project (mytest VERSION 1.2.3.4 LANGUAGES “CXX”)

3、add_executable (<name> [WIN32] [MACOSX_BUNDLE]   //可执行目标文件的名字，在一个cmake工程中，这个名字必须全局唯一。
    [EXCLUDE_FROM_ALL]                              //用于指定可执行目标是否会被构建，当该选项使用的时候，可执行目标不会被构建。
    [source1] [source2 ...])                        //构建可执行目标文件所需要的源文件。
