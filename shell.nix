{ pkgs-unstable ? import <nixpkgs> {} }:

pkgs-unstable.mkShell {
    buildInputs = with pkgs-unstable;[
        gcc sfml
        libGLU
        cmake
        glfw-wayland
        glfw
        gdb
    ];
}
