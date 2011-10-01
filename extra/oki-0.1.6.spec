Summary: Small platform game.
Name: oki
Version: 0.1.6
Release: 1
Copyright: GPL
Group: Amusements/Games
Source: http://free.of.pl/s/szatkus/soft/gry/oki-0.1.6.tar.gz
BuildRoot: /var/tmp/%{name}-buildroot

%description
Small platform game with monochrome graphic.

%prep
%setup -q

%build
./configure
make RPM_OPT_FLAGS="$RPM_OPT_FLAGS"

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/games/oki
mkdir -p $RPM_BUILD_ROOT/usr/games/oki/docs
mkdir -p $RPM_BUILD_ROOT/usr/games/oki/gfx
mkdir -p $RPM_BUILD_ROOT/usr/games/oki/maps
mkdir -p $RPM_BUILD_ROOT/usr/games/oki/snd

install -s -m 755 oki $RPM_BUILD_ROOT/usr/games/oki
install -s -m 755 oki_me $RPM_BUILD_ROOT/usr/games/oki
install -m 755 README $RPM_BUILD_ROOT/usr/games/oki
install -m 755 COPYING $RPM_BUILD_ROOT/usr/games/oki
install -m 755 CHANGELOG $RPM_BUILD_ROOT/usr/games/oki
install -m 755 TODO $RPM_BUILD_ROOT/usr/games/oki
cp -rf docs $RPM_BUILD_ROOT/usr/games/oki
cp -rf gfx $RPM_BUILD_ROOT/usr/games/oki
cp -rf maps $RPM_BUILD_ROOT/usr/games/oki
cp -rf snd $RPM_BUILD_ROOT/usr/games/oki

mkdir -p $RPM_BUILD_ROOT/usr/share/applications
install -m 644 extra/oki.desktop $RPM_BUILD_ROOT/usr/share/applications

mkdir -p $RPM_BUILD_ROOT/usr/share/pixmaps
install -m 644 gfx/oki40.png $RPM_BUILD_ROOT/usr/share/pixmaps/oki.png

mkdir -p $RPM_BUILD_ROOT/usr/bin
install -m 755 extra/oki_bash $RPM_BUILD_ROOT/usr/bin/oki

%clean
rm -rf $RPM_BUILD_ROOT/usr/games/oki

%files
%defattr(-,root,root)
/usr/games/oki
/usr/games/oki/docs
/usr/games/oki/docs/ball.png
/usr/games/oki/docs/bmaker.png
/usr/games/oki/docs/bomb.png
/usr/games/oki/docs/checkpoint.png
/usr/games/oki/docs/cloner.png
/usr/games/oki/docs/coin.png
/usr/games/oki/docs/dasher.png
/usr/games/oki/docs/dball.png
/usr/games/oki/docs/door.png
/usr/games/oki/docs/ellyssyss.png
/usr/games/oki/docs/exit.png
/usr/games/oki/docs/gozel2.png
/usr/games/oki/docs/gozel.png
/usr/games/oki/docs/guide.html
/usr/games/oki/docs/height.png
/usr/games/oki/docs/jump.png
/usr/games/oki/docs/key.png
/usr/games/oki/docs/life.png
/usr/games/oki/docs/man.png
/usr/games/oki/docs/med.png
/usr/games/oki/docs/needle.png
/usr/games/oki/docs/needles.png
/usr/games/oki/docs/oki.png
/usr/games/oki/docs/pakman.png
/usr/games/oki/docs/robo.png
/usr/games/oki/docs/rock.png
/usr/games/oki/docs/run.png
/usr/games/oki/docs/shield.png
/usr/games/oki/docs/speed.png
/usr/games/oki/docs/start.png
/usr/games/oki/docs/strength.png
/usr/games/oki/docs/trap.png
/usr/games/oki/docs/txt.png
/usr/games/oki/docs/upper.png
/usr/games/oki/docs/water.png
/usr/games/oki/docs/water_stop.png
/usr/games/oki/docs/water_up.png
/usr/games/oki/gfx
/usr/games/oki/gfx/boom.png
/usr/games/oki/gfx/events.png
/usr/games/oki/gfx/exit.png
/usr/games/oki/gfx/font.png
/usr/games/oki/gfx/killed.png
/usr/games/oki/gfx/logo.png
/usr/games/oki/gfx/man.png
/usr/games/oki/gfx/monster10.png
/usr/games/oki/gfx/monster11.png
/usr/games/oki/gfx/monster12.png
/usr/games/oki/gfx/monster1.png
/usr/games/oki/gfx/monster2.png
/usr/games/oki/gfx/monster3.png
/usr/games/oki/gfx/monster4.png
/usr/games/oki/gfx/monster5.png
/usr/games/oki/gfx/monster6.png
/usr/games/oki/gfx/monster7.png
/usr/games/oki/gfx/monster8.png
/usr/games/oki/gfx/monster9.png
/usr/games/oki/gfx/oke.png
/usr/games/oki/gfx/oki10.png
/usr/games/oki/gfx/oki20.png
/usr/games/oki/gfx/oki40.png
/usr/games/oki/gfx/oki.ico
/usr/games/oki/gfx/oki_new.png
/usr/games/oki/gfx/oki.png
/usr/games/oki/gfx/rock.png
/usr/games/oki/gfx/text.png
/usr/games/oki/gfx/tileset.png
/usr/games/oki/gfx/torch.png
/usr/games/oki/maps
/usr/games/oki/maps/default
/usr/games/oki/maps/default/lev5.map
/usr/games/oki/maps/default/lev4.map
/usr/games/oki/maps/default/lev2.map
/usr/games/oki/maps/default/lev3.map
/usr/games/oki/maps/default/index
/usr/games/oki/maps/default/map.png
/usr/games/oki/maps/default/lev.map
/usr/games/oki/maps/custom
/usr/games/oki/maps/custom/custom1.map
/usr/games/oki/maps/custom/custom_map.png
/usr/games/oki/maps/custom/index
/usr/games/oki/maps/custom/custom2.map
/usr/games/oki/maps/bth
/usr/games/oki/maps/bth/bth2.map
/usr/games/oki/maps/bth/index
/usr/games/oki/maps/bth/bth3.map
/usr/games/oki/maps/bth/bth.png
/usr/games/oki/maps/bth/bth1.map
/usr/games/oki/maps/bth/bth4.map
/usr/games/oki/maps/maps
/usr/games/oki/snd
/usr/games/oki/snd/bonus.wav
/usr/games/oki/snd/boom.wav
/usr/games/oki/snd/click.wav
/usr/games/oki/snd/cursor.wav
/usr/games/oki/snd/death.wav
/usr/games/oki/snd/hit.wav
/usr/games/oki/snd/jump.wav
/usr/games/oki/oki
/usr/games/oki/oki_me
/usr/games/oki/COPYING
/usr/games/oki/README
/usr/share/applications/oki.desktop
/usr/share/pixmaps/oki.png
/usr/bin/oki

%changelog
