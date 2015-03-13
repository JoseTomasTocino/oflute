<font size='4'><font color='red'><b>ATTENTION:</b></font> <b>this project is no longer updated nor mantained</b>. Also, bear in mind that latest versions of Ubuntu broke compatibility with some base libraries so oFlute won't work on them either.</font>

![http://oflute.googlecode.com/svn/web/logotipo.png](http://oflute.googlecode.com/svn/web/logotipo.png)

**oFlute** is a musical game in which the player has to play the recorder properly to get points, following a musical staff. Also, it features a couple of basic lessons about how to play the recorder and learning the basics of music.

I'm developing it as my final degree project.

## Dependencies & installation ##
If you're on a debian-based distribution, these are the dependencies for gosu:
```
sudo apt-get install g++ libgl1-mesa-dev libpango1.0-dev \
libopenal-dev libsndfile-dev libxdamage-dev libsdl-ttf2.0-dev \
libboost-dev libfreeimage3 libfreeimage-dev
```

Next, these are the oFlute-only dependencies:
```
sudo apt-get install libboost-regex-dev libboost-filesystem-dev \
libboost-thread-dev libpulse-dev
```

Next, you can checkout the code from the svn:
```
svn checkout http://oflute.googlecode.com/svn/trunk/ oflute
```

After that, compile the graphic library, then the project:
```
cd oflute
make libgosu
make
```

The executable is called `oflute`, so you can launch it using:
```
./oflute
```