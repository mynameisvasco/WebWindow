# WebWindowX
This fork of WebWindow provides new features to the library and
removes completely Blazor support.

For information, see [this blog post](https://blog.stevensanderson.com/2019/11/18/2019-11-18-webwindow-a-cross-platform-webview-for-dotnet-core/).

# Usage instructions

Unless you want to change the `WebWindowX` library itself, you do not need to build this repo yourself. If you just want to use it in an app, grab the [prebuilt NuGet package](https://www.nuget.org/packages/WebWindowX) or follow [these 'hello world' example steps](https://blog.stevensanderson.com/2019/11/18/2019-11-18-webwindow-a-cross-platform-webview-for-dotnet-core/).

# How to build this repo

If you want to build the `WebWindowX` library itself, you will need:

 * If you're on Windows:
   * Use Visual Studio with C++ support enabled. You *must* build in x64 configuration (*not* AnyCPU, which is the default).
 * If you're on macOS:
   * Install Xcode so that you have the whole `gcc` toolchain available on the command line.
   * From the repo root, run `dotnet build src/WebWindow/WebWindow.csproj`
 * If you're on Linux (tested with Ubuntu 18.04):
   * Install dependencies: `sudo apt-get update && sudo apt-get install libgtk-3-dev libwebkit2gtk-4.0-dev libnotify-dev`
   * From the repo root, run `dotnet build src/WebWindow/WebWindow.csproj`
 * If you're on Windows Subsystem for Linux (WSL), then as well as the above, you will need a local X server ([example setup](https://virtualizationreview.com/articles/2017/02/08/graphical-programs-on-windows-subsystem-on-linux.aspx)).

