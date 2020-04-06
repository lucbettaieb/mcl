# MCL
cc_library(
  name="mcl",
  hdrs=glob(["include/mcl/**/*"]),
  srcs=glob(["src/particle_filter.cpp"]),
  # strip_include_prefix="include",
  include_prefix="mcl",
  deps=[
    "@yaml-cpp//:yaml-cpp",
  ],
  # copts = ["-Iinclude"], # This is the key part
  visibility=["//visibility:public"],
)

# cc_binary(
#   name = "mcl_node",
#   srcs = ["src/mcl_node.cpp"],
#   deps = ["mcl"]
# )
#   