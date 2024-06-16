{ pkgs-unstable ? import <nixpkgs> {} }:

pkgs-unstable.mkShell {
    buildInputs = with pkgs-unstable;[
        gcc 
        gnumake
        cmake
        sfml
        libGLU
        glfw-wayland
        glfw
    ];
}
