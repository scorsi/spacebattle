# SpaceBattle

SpaceBattle is a game created and designed in case of school project by:

- Sylvain CORSINI

- Florentin BONNAY

- Jasmin SAIPI

## Dependencies

- gcc/g++ (recommanded 5.4.0 or more)

- CMake (recommanded 3.5 or more)

- conan (recommanded 1.8.4 or more)

### CMake and gcc/g++

#### Linux Ubuntu 16.04/18.04 LTS

```shell
apt-get install -y cmake gcc g++
```

#### MacOS

You need [XCode](https://developer.apple.com/xcode/) installed to use CMake, g++ and gcc.

```shell
xcode-select --install
```

### Conan

To install conan, it is recommanded to install from pip using python3.

#### Linux Ubuntu 16.04/18.04 LTS via Python3

```shell
apt-get install -y python3 python3-pip
pip3 install conan
```

#### MacOS via Python3 (recommanded)

```shell
brew install python3
pip3 install conan
```

##### For more information or platforms (Windows, Debian or Arch) go to [conan.io](https://conan.io/downloads.html).

## More dependencies

- Bincrafters conan remote

### Bincrafters conan remote

```shell
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```
