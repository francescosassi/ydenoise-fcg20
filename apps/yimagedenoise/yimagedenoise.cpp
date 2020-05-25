#include <yocto/yocto_commonio.h>
namespace cli = yocto::commonio;

#include <yocto_extension/yocto_extension.h>
namespace dns = yocto::extension;

#include "ext/utils/image_io.h"

#include <yocto/yocto_image.h>
namespace img = yocto::image;

#include <yocto/yocto_math.h>
using namespace yocto::math;


using namespace std::string_literals;

int main(int argc, const char* argv[]) {
  // options
  auto param = ""s;
  auto out_file   = "out.png"s;
  auto in_file = "img.png"s;
  auto type = "nlmean"s;

  // parse command line
  auto cli = cli::make_cli("yimagedenoise", "Intel Denoiser");
  add_option(cli, "--type,-t", type, "Output image filename", true);
  add_option(cli, "--outimage,-o", out_file, "Output image filename", true);
  add_option(cli, "image", in_file, "Input image filename", true);
  parse_cli(cli, argc, argv);

  if (type == "nlmean"){
    printf("nlmean\n");
    
    // error buffer
    auto ioerror = ""s;

    // load
    auto img = img::image<vec4f>{};

    if (!load_image(in_file, img, ioerror)) cli::print_fatal(ioerror);

    // corrections
    
    img = dns::denoise_nlmean(img, 21, 3, 15, 0.4 * 15);

    // save
    if (!save_image(out_file, float_to_byte(img), ioerror))
      cli::print_fatal(ioerror);
  } 
  else {

    auto buffer = oidn::loadImage(in_file);
    printf("ciao\n");
    const int width  = buffer.getWidth();
    const int height = buffer.getHeight();
    printf("%d %d\n", width, height);
    oidn::ImageBuffer output(width, height, 3);
    printf("%p \n", buffer.getData());
    printf("%p \n", output.getData());
    //output.getData();
    dns::denoise(buffer.getData(), output.getData(), width, height);
    oidn::saveImage(out_file, output);
  }

  return 0;
}