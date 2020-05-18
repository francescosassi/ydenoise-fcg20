//
// Implementation for Yocto/Extension.
//

//
// LICENSE:
//
// Copyright (c) 2020 -- 2020 Fabio Pellacini
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "yocto_extension.h"

#include <atomic>
#include <deque>
#include <future>
#include <memory>
#include <mutex>
using namespace std::string_literals;

// -----------------------------------------------------------------------------
// IMPLEMENTATION FOR EXTENSION
// -----------------------------------------------------------------------------
namespace yocto::extension {

    img::image<vec4f> denoise_nlmean(const img::image<vec4f>& img){
        auto out = img;
        auto width = out.size().x;
        auto height = out.size().y;
        printf("width = %d", width);
        printf("height = %d", height);
        for (auto i=0 ; i < width * height; i++){
            out[i] = math::pow(out[i], (1/2.2));
        }
        
        return out;

        return img;
    }

    void denoise(float* colorPtr, float* outputPtr, int width, int height){
        // Create an Intel Open Image Denoise device
        printf("ciaoo2\n");
        oidn::DeviceRef device = oidn::newDevice();
        const char* errorMessage;
        if (device.getError(errorMessage) != oidn::Error::None)
            throw std::runtime_error(errorMessage);
        device.commit();
        //printf("ciaoo\n");
        // Create a denoising filter
        oidn::FilterRef filter = device.newFilter("RT"); // generic ray tracing filter
        filter.setImage("color",  colorPtr,  oidn::Format::Float3, width, height);
        //filter.setImage("albedo", albedoPtr, oidn::Format::Float3, width, height); // optional
        //filter.setImage("normal", normalPtr, oidn::Format::Float3, width, height); // optional
        filter.setImage("output", outputPtr, oidn::Format::Float3, width, height);
        filter.set("hdr", false); // image is HDR
        filter.commit();

        // Filter the image
        filter.execute();

        // Check for errors
        if (device.getError(errorMessage) != oidn::Error::None){
            printf("Error: %s\n", errorMessage);
        }

    }


}  // namespace yocto::pathtrace
