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
  auto albedo_file = "albedo.jpg"s;
  auto normal_file = "normal.jpg"s;
  auto type = "nlmean"s;
  auto sigma = 7.0f;
  auto r = 1;
  auto f = 1;
  auto h = 1.0f;

  // parse command line
  auto cli = cli::make_cli("yimagedenoise", "Intel Denoiser");
  add_option(cli, "--type,-t", type, "Output image filename", true);
  add_option(cli, "--albedo,-a", albedo_file, "Albedo for AI Denoise", false);
  add_option(cli, "--normal,-n", normal_file, "Normals for AI Denoise", false);
  add_option(cli, "--sigma,-s", sigma, "Sigma for nl means", false);
  add_option(cli, "--radius,-r", r, "Radius image filename", false);
  add_option(cli, "--frame,-f", f, "Frame image filename", false);
  add_option(cli, "--height,-h", h, "Height image filename", false);
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


    img = dns::denoise_nlmean(img, r, f, sigma, h);

    // save
    if (!save_image(out_file, img, ioerror))
      cli::print_fatal(ioerror);
  } 
  else {

    auto buffer = oidn::loadImage(in_file);

    const int width  = buffer.getWidth();
    const int height = buffer.getHeight();

    oidn::ImageBuffer output(width, height, 3);

    auto albedo_bool = false;
    auto normal_bool = false;

    oidn::ImageBuffer albedo(width, height, 3);
    if (albedo_file != "albedo.jpg"){
        albedo = oidn::loadImage(albedo_file);
        auto albedo_bool = true;
    }

    oidn::ImageBuffer normal(width, height, 3);
    if (normal_file != "normal.jpg"){
        auto normal = oidn::loadImage(normal_file);
        auto normal_bool = true;
    }
    
    if (albedo_bool && normal_bool){
      dns::denoise(buffer.getData(), albedo.getData(), normal.getData(), output.getData(), width, height);
    }
    else if (albedo_bool && !normal_bool) {
      dns::denoise(buffer.getData(), albedo.getData(), nullptr, output.getData(), width, height);
    }   
    else if (!albedo_bool && normal_bool) {
      dns::denoise(buffer.getData(), nullptr, normal.getData(), output.getData(), width, height);
    }
    else {
      dns::denoise(buffer.getData(), nullptr, nullptr, output.getData(), width, height);
    }

    oidn::saveImage(out_file, output);
  }

  return 0;
}