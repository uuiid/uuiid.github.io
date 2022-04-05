//
// Created by TD on 2022/4/5.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>

#include <fmt/format.h>

int main(int argc, char *argv[]) {
    std::stringstream istringstream_source{"sanduiosahfpdsjfsdnfbgvfzx0-i["
                                           "ksz["
                                           "fjpisf"};
    std::stringstream istringstream_target{};
    boost::iostreams::filtering_streambuf<boost::iostreams::input> filteringStreambuf{};
    filteringStreambuf.push(boost::iostreams::zlib_compressor{});
    filteringStreambuf.push(istringstream_source);
    boost::iostreams::copy(filteringStreambuf, istringstream_target);

    std::cout << fmt::format("str |{}| -> |{:#x}|", istringstream_source.str(), fmt::join(istringstream_target.str()," "));

}
