# Set the name of the product
set(PRODUCT_NAME ${PROJECT_NAME})
# Set the version
set(PRODUCT_VERSION_MAJOR "0")
set(PRODUCT_VERSION_MINOR "1")

# Type can be "git", "beta", "release"
set(PRODUCT_VERSION_TYPE "git")

# Create some handy strings
set(PRODUCT_VERSION_STRING "${PRODUCT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}-${PRODUCT_VERSION_TYPE}")
set(PRODUCT_STRING "${PRODUCT_NAME} v${PRODUCT_VERSION_STRING}")

set(PROJECT_EXEC "reamp")
