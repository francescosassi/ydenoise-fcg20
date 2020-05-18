#include <yocto/yocto_commonio.h>
namespace cli = yocto::commonio;

#include <yocto_extension/yocto_extension.h>
namespace dns = yocto::extension;

#include "ext/utils/image_io.h"
using namespace std::string_literals;

#include <yocto/yocto_image.h>
#include <yocto/yocto_math.h>
using namespace yocto::math;
namespace cli = yocto::commonio;
namespace img = yocto::image;
using namespace std::string_literals;

int main(int argc, const char* argv[]) {
  // options
  auto param = ""s;
  auto output   = "out.png"s;
  auto filename = "img.png"s;
  auto type = "nlmean"s;

  // parse command line
  auto cli = cli::make_cli("yimagedenoise", "Intel Denoiser");
  add_option(cli, "--type,-t", type, "Output image filename", true);
  add_option(cli, "--outimage,-o", output, "Output image filename", true);
  add_option(cli, "image", filename, "Input image filename", true);
  parse_cli(cli, argc, argv);

  if (type == "nlmean"){
    printf("nlmean\n");
    
    // error buffer
    auto ioerror = ""s;

    // load
    auto img = img::image<vec4f>{};

    if (!load_image(filename, img, ioerror)) cli::print_fatal(ioerror);

    // corrections
    img = dns::denoise_nlmean(img);

    // save
    if (!save_image(output, float_to_byte(img), ioerror))
      cli::print_fatal(ioerror);
  } else {

    auto buffer = oidn::loadImage("tests/cornellbox.pfm");
    printf("ciao\n");
    const int width  = buffer.getWidth();
    const int height = buffer.getHeight();
    printf("%d %d\n", width, height);
    oidn::ImageBuffer output(width, height, 3);
    printf("%p \n", buffer.getData());
    printf("%p \n", output.getData());
    //output.getData();
    dns::denoise(buffer.getData(), output.getData(), width, height);
    oidn::saveImage("tests/test_denoised.pfm", output);

  }


  return 0;
}