#include <iostream>
#include "struct_pack/struct_pack.hpp"


template <typename... Args> std::string pack(Args &&...args) {
  auto bodySize = struct_pack::get_needed_size(std::tuple<Args...>(std::forward<Args>(args)...));//buggy can't use forward 
  //auto bodySize = struct_pack::get_needed_size(std::tuple<Args...>(args...)); 
  return struct_pack::serialize<std::string>(std::tuple<Args...>(args...));
}

template <typename... Args> void unpack(const std::string &buf) {
  std::tuple<Args...> rst;
  struct_pack::deserialize_to(rst, buf);
  std::cout << "result :" << std::get<0>(rst) << std::endl;
  std::cout << "result :" << std::get<1>(rst) << std::endl;
}

int  main(int , char * argv[]) {

  auto pkMsg = pack<std::string, int32_t>("hello", 3333);

  unpack<std::string, int32_t>(pkMsg);
}


//use forward output : ( "hello" is misssing )
//result :
//result :3333



//don't use forward output : 
//result :hello
//result :3333
