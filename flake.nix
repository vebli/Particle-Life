{
    inputs.nixpkgs.url = "nixpkgs/nixos-unstable";
    outputs = {self, nixpkgs, ...}: let 
        system = "x86_64-linux";
        pkgs = import nixpkgs {inherit system;};
    in
    {
        packages.${system}.default = pkgs.stdenv.mkDerivation {
                name = "Particle-Life";
                src = ./.;
                buildInputs = with pkgs; [
                    gcc
                    gnumake
                    cmake
                    sfml
                    libGLU
                    glfw-wayland
                    glfw
                ];
                configurePhase = ''
                    mkdir -p build   
                    cd build  
                    cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
                    mkdir -p bin
                    '';
                buildPhase = '' 
                    cmake --build .
                    '';
                installPhase = ''
                    mkdir -p "$out/bin"
                    cp Particle-Life $out/bin/
                '';
        };

        app.${system}.default = {
            type = "app";
            program = "${self.packages.${system}.default}/bin/Particle-Life";
        };

    };
}
