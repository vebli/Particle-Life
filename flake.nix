{
  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    nix-systems.url = "github:nix-systems/default";
  };
  outputs = inputs @ {
    self,
    nixpkgs,
    ...
  }: let
    eachSystem = nixpkgs.lib.genAttrs (import inputs.nix-systems);
    mkPkgs = system: nixpkgs.legacyPackages.${system};
  in {
    packages = eachSystem (system: let
      pkgs = mkPkgs system;
    in {
      default = pkgs.stdenv.mkDerivation {
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
          cmake -DCMAKE_BUILD_TYPE=Release ..
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
    });
    apps = eachSystem (system: {
      default = {
        type = "app";
        program = "${self.packages.${system}.default}/bin/Particle-Life";
      };
    });
  };
}
