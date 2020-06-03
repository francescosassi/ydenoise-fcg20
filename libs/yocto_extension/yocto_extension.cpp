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
namespace img = yocto::image;

// -----------------------------------------------------------------------------
// IMPLEMENTATION FOR EXTENSION
// -----------------------------------------------------------------------------
namespace yocto::extension {

    template <typename Func>
    inline void parallel_for(const vec2i& size, Func&& func) {
    auto             futures  = std::vector<std::future<void>>{};
    auto             nthreads = std::thread::hardware_concurrency();
    std::atomic<int> next_idx(0);
    for (auto thread_id = 0; thread_id < nthreads; thread_id++) {
        futures.emplace_back(
            std::async(std::launch::async, [&func, &next_idx, size]() {
            while (true) {
                auto j = next_idx.fetch_add(1);
                if (j >= size.y) break;
                for (auto i = 0; i < size.x; i++) func({i, j});
            }
            }));
    }
    for (auto& f : futures) f.get();
    }

    img::image<vec4f> denoise_nlmean(const img::image<vec4f>& img, int r, int f, float sigma, float h){

        auto out = img::image<vec4f>(img.size());
        parallel_for(img.size(), [&out, img, r, f, sigma, h](const vec2i& ij) {

        auto width = img.size().x;
        auto height = img.size().y;
        auto i = ij.x;
        auto j = ij.y;
        auto p = img[{i, j}];
        //printf("%f %f %f\n", p.x, p.y, p.z);
        auto c = 0.0f;
        auto acc = vec4f{0, 0, 0, 0};
        //iterate in the neigh of size (2* r x 2 * r)
        
        for(int rx = -r; rx < r; rx++){
            for(int ry = -r; ry < r; ry++){
                auto qx = i + rx;
                auto qy = j + ry;
                //if(qx == i && qy == j) continue;
                if (!img.contains({qx, qy})) continue;
                auto q = img[{i + rx, j + ry}];

                auto tot = vec4f{0, 0, 0, 0};
                // iterate in the neigh of size (2* f x 2 * f)
                // centered in p and q

                for(int fx = -f; fx < f; fx++){
                    for(int fy = -f; fy < f; fy++){
                        if (!img.contains({qx + fx,  qy + fy})) continue;
                        if (!img.contains({i + fx,  j + fy})) continue;
                        auto qf = img[{qx + fx, qy + fy}];
                        auto pf = img[{i + fx, j + fy}];
                        //printf("1 %f %f %f\n",qf.x, qf.y, qf.z);
                        //printf("2 %f %f %f\n",pf.x, pf.y, pf.z);
                        tot += pow((pf - qf) * 255, 2);
                        //printf("2 %f %f %f\n",tot.x, tot.y, tot.z);
                        //
                    }
                }
                
                //auto d_tot = tot.x + tot.y + tot.z;
                //printf("tpt: %f\n", tot);
                auto dist = sum(tot) / (3.0f * pow(2.0f * f, 2));
                //printf("%f\n", dist);
                auto w = exp(-max(dist - 2 * pow(sigma, 2), 0.0f) / pow(h, 2));
                //printf("%f\n", w);
                //printf("%f", w);
                c += w;
                acc += q * w;
            }

        }
        acc/=c;
        //printf("%f %f %f\n", acc.x, acc.y, acc.z);
        out[{i, j}] = acc;
        //out[{i, j}] = pow(acc, (1/2.2f));
        });

        return out;
    }

    img::image<vec4f> denoise_nlmean_patch(const img::image<vec4f>& img, int r, int f, float sigma, float h){

        auto out = img::image<vec4f>(img.size());
        parallel_for(img.size(), [&out, img, r, f, sigma, h](const vec2i& ij) {

        auto width = img.size().x;
        auto height = img.size().y;
        auto i = ij.x;
        auto j = ij.y;
        auto p = img[{i, j}];
        //printf("%f %f %f\n", p.x, p.y, p.z);
        auto c = 0.0f;
        auto acc = vec4f{0, 0, 0, 0};
        //iterate in the neigh of size (2* r x 2 * r)
        
        for(int rx = -r; rx < r; rx++){
            for(int ry = -r; ry < r; ry++){
                auto qx = i + rx;
                auto qy = j + ry;
                //if(qx == i && qy == j) continue;
                if (!img.contains({qx, qy})) continue;
                auto q = img[{i + rx, j + ry}];

                auto tot = vec4f{0, 0, 0, 0};
                // iterate in the neigh of size (2* f x 2 * f)
                // centered in p and q

                for(int fx = -f; fx < f; fx++){
                    for(int fy = -f; fy < f; fy++){
                        if (!img.contains({qx + fx,  qy + fy})) continue;
                        if (!img.contains({i + fx,  j + fy})) continue;
                        auto qf = img[{qx + fx, qy + fy}] * 255;
                        auto pf = img[{i + fx, j + fy}] * 255;
                        //printf("1 %f %f %f\n",qf.x, qf.y, qf.z);
                        //printf("2 %f %f %f\n",pf.x, pf.y, pf.z);
                        tot += (pf - qf) * (pf - qf);
                        //printf("2 %f %f %f\n",tot.x, tot.y, tot.z);
                        //
                    }
                }
                
                //auto d_tot = tot.x + tot.y + tot.z;
                //printf("tpt: %f\n", tot);
                auto dist = sum(tot) / (3.0f *  (2 * f + 1) * (2 * f + 1));
                //printf("%f\n", dist);
                auto w = exp(-max(dist - 2 * (sigma * sigma), 0.0f) / (h * h));
                //printf("%f\n", w);
                //printf("%f", w);
                c += w;
                acc += q * w;
            }

        }
        //printf("%f\n", c);
        acc/=c;
        //printf("%f %f %f\n", acc.x, acc.y, acc.z);
        out[{i, j}] = acc;
        });

        return out;
    }

    void denoise(float* color, float* albedo, float* normal, float* output, int width, int height){
        // Create an Intel Open Image Denoise device
        oidn::DeviceRef device = oidn::newDevice();
        const char* errorMessage;
        if (device.getError(errorMessage) != oidn::Error::None)
            throw std::runtime_error(errorMessage);
        device.commit();
        // Create a denoising filter
        oidn::FilterRef filter = device.newFilter("RT"); // generic ray tracing filter
        filter.setImage("color",  color,  oidn::Format::Float3, width, height);
        if(albedo != nullptr){
            filter.setImage("albedo", albedo, oidn::Format::Float3, width, height);
        }
        if(normal != nullptr){
            filter.setImage("normal", normal, oidn::Format::Float3, width, height);
        }
        filter.setImage("output", output, oidn::Format::Float3, width, height);
        filter.set("hdr", true); // image is HDR
        filter.commit();

        // Filter the image
        filter.execute();

        // Check for errors
        if (device.getError(errorMessage) != oidn::Error::None){
            printf("Error: %s\n", errorMessage);
        }

    }


}  // namespace yocto::pathtrace
