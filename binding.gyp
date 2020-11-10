{
    "targets": [{
        "target_name": "t9602-rpi",
        "cflags!": [ "-fno-exceptions -nostartfiles" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "addon.cc",
            "t9602.cc",
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}