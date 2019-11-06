## Web-Server

## Introduction   
An implementation of HTTP server based on **c++11**, which is easily to add a cgi instance. It can handle static resources, support HTTP long connections, and so on. We also implement the [Asynchronous Log](https://github.com/stepByStepToSky/ThreadPool-and-Asynchronous-log) to record the status of the server.

Test page ：[ExampleCgi](http://106.54.211.174:9508/cgi-bin/example?name=lufan&id=2021) and [LoginCgi](http://106.54.211.174:9508/cgi-bin/login).

## Build
a) To Compile source files into binary executables (in the root folder)
```cmd
mkdir build && cd build
cmake ..
make
```

b) Run the program (in the build folder)
```cmd
./httpcgiservermain
```

## Steps of adding a Cgi instance
a) Write a Cgi instance class, which inherits the BaseCgi class, like [ExampleCgi](https://github.com/stepByStepToSky/Web-Server/blob/master/exampleCgi/examplecgi.h).

b) Add the Cgi instance into the [CgiInstanceFactory](https://github.com/stepByStepToSky/Web-Server/blob/master/cgidispatch.cpp).

c) Add the header file into the [CgiHeader](https://github.com/stepByStepToSky/Web-Server/blob/master/includecgiheader.h).

d) Modify the [CMakeLists.txt](https://github.com/stepByStepToSky/Web-Server/blob/master/CMakeLists.txt).

e) Then build and run.

## Repository contents
See implDoc.md for a brief overview of the implementation.
Guide to header files:
- **base/log.h** Interface for log system, which is from [Asynchronous Log](https://github.com/stepByStepToSky/ThreadPool-and-Asynchronous-log).

- **epoller.h** Encapsulate related functions of epoll.
- **netutil.h** Encapsulate related functions of socket fd.
- **simplebuffer.h** Application layer buffer(we only implement the LT model now).
- **channel.h** Encapsulate channel(event) related callback functions (read/write/error functions).
- **eventloop.h** It manage the channel(event), which is registed to the epoller, and process the active channels(events).
- **tcpserver.h** When read event happends, it automatically read the byte stream into the application buffer of the channel, and execute the read callback function. The same as write and error events happend.
- **httpmessage.h** Parse the HTTP request, build HTTP respond message. Here, we use a state machine to process HTTP requests.
- **basecgi.h** The abstract class of Cgi instance class. It provides a Process interface, we use it to process the cgi request.
- **includecgiheader.h** Include the Cgi instance class, which is used for cgidispatch.
- **cgidispatch.h** The Cgi dispatcher, which use the url to find the Cgi instance, to execute the cgi program.
- **httpcgiserver.h** When read event happend, it firstly parses the http request in the application buffer of the channel, then finds the cgi instance and process the request.
- **httpcgiservermain.cpp** HTTP server main.
- **exampleCgi/examplecgi.h and loginCgi/logincgi.h** Example of how to write a Cgi instance class. webFile/login includes the .html, .js, .css files needed by the LoginCgi class.
