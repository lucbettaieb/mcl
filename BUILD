# MCL
cc_library(
  name="mcl",
  hdrs=glob(["include/mcl/**/*"]),
  srcs=glob(["src/particle_filter.cpp"]),
  include_prefix="mcl",
  deps=[
    "@yaml-cpp//:yaml-cpp",
  ],
  visibility=["//visibility:public"],
)

# cc_binary(
#   name = "mcl_node",
#   srcs = ["src/mcl_node.cpp"],
#   deps = ["mcl"]
# )
#