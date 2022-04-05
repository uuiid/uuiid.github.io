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

    std::stringstream stringstream_source{};
    std::stringstream stringstream_target{};
    if (argc > 1) {
        stringstream_source << argv[1];
    } else {
        stringstream_source << "std::stringstream stringstream_source{}";
    }
    boost::iostreams::filtering_streambuf<boost::iostreams::input> filteringStreambuf{};
    filteringStreambuf.push(boost::iostreams::zlib_compressor{});
    filteringStreambuf.push(stringstream_source);
    boost::iostreams::copy(filteringStreambuf, stringstream_target);

    std::cout << fmt::format("str |{}| -> |{:#x}|", stringstream_source.str(),
                             fmt::join(stringstream_target.str(), " "));

}
