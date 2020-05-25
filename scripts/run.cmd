:: bin\Release\yscenetrace.exe tests\01_cornellbox\cornellbox.json -o out\lowres\01_cornellbox_512_256.png -s 64 -r 512
:: bin\yscenetrace.exe tests\02_matte\matte.json -o out\lowres\02_matte_720_256.jpg -s 25 -r 720
:: bin\yscenetrace.exe tests\03_texture\texture.json -o out\lowres\03_texture_720_256.jpg -s 256 -r 720
:: bin\yscenetrace.exe tests\04_envlight\envlight.json -o out\lowres\04_envlight_720_256.jpg -s 256 -r 720
:: bin\yscenetrace.exe tests\05_arealight\arealight.json -o out\lowres\05_arealight_720_256.jpg -s 256 -r 720
:: bin\yscenetrace.exe tests\06_metal\metal.json -o out\lowres\06_metal_720_256.jpg -s 256 -r 720
:: bin\yscenetrace.exe tests\07_plastic\plastic.json -o out\lowres\07_plastic_720_256.jpg -s 256 -r 720
:: bin\yscenetrace.exe tests\08_glass\glass.json -o out\lowres\08_glass_720_256.jpg -s 256 -b 8 -r 720
:: bin\yscenetrace.exe tests\09_opacity\opacity.json -o out\lowres\09_opacity_720_256.jpg -s 256 -r 720
:: bin\yscenetrace.exe tests\10_hair\hair.json -o out\lowres\10_hair_720_256.jpg -s 256 -r 720
:: bin\yscenetrace.exe tests\11_bathroom1\bathroom1.json -o out\lowres\11_bathroom1_720_256.jpg -s 256 -b 8 -r 720
:: bin\yscenetrace.exe tests\12_ecosys\ecosys.json -o out\lowres\12_ecosys_720_256.jpg -s 64 -r 720

bin\RelWithDebInfo\yimagedenoise.exe out\lowres\01_cornellbox_512_256.png -o out\lowres\01_cornellbox_512_256_clean.png -t nlmean