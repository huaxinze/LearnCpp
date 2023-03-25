# A Hello CMake
* 1、cmake_minimum_required(VERSION \<min\>[...\<max\>] [FATAL_ERROR])&emsp;&emsp;// 用于指定cmake的最低和最高版本，用于做版本控制cmake_minimum_required (VERSION 3.10.0...3.12.0)

* 2、project(\<PROJECT-NAME\>&emsp;&emsp;//用于指定cmake工程的名称 project (mytest) \
&emsp;[VERSION \<major\>[.\<minor\>[.\<patch\>[.\<tweak\>]]]]&emsp;&emsp;//用于指定cmake工程的版本号 project (mytest VERSION 1.2.3.4) \
&emsp;[DESCRIPTION \<project-description-string\>]&emsp;&emsp;//用于对工程的文本描述 project (mytest DESCRIPTION “This is mytest project.”) \
&emsp;[HOMEPAGE_URL \<url-string\>]&emsp;&emsp;//用于指定工程的主页URL project (mytest HOMEPAGE_URL “https://www.XXX(示例).com”) \
&emsp;[LANGUAGES \<language-name\>...]))&emsp;&emsp;//用于选择构建工程需要的编程语言 project (mytest VERSION 1.2.3.4 LANGUAGES “CXX”)

* 3、add_executable (\<name\> [WIN32] [MACOSX_BUNDLE]&emsp;&emsp;//可执行目标文件的名字，在一个cmake工程中，这个名字必须全局唯一。 \
&emsp;[EXCLUDE_FROM_ALL]&emsp;&emsp;//用于指定可执行目标是否会被构建，当该选项使用的时候，可执行目标不会被构建。 \
&emsp;[source1] [source2 ...])&emsp;&emsp;//构建可执行目标文件所需要的源文件。
