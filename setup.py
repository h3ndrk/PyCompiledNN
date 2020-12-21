import os
import pathlib
import setuptools
import setuptools.command.build_ext


class CMakeExtension(setuptools.Extension):
    def __init__(self, name, sources=[]):
        super().__init__(name=name, sources=sources)


class BuildCMakeExt(setuptools.command.build_ext.build_ext):
    def run(self):
        for extension in self.extensions:
            if extension.name == 'PyCompiledNN':
                self.build_cmake(extension)
        super().run()

    def build_cmake(self, extension: setuptools.Extension):
        source_directory = pathlib.Path().absolute()

        self.announce('Preparing the build environment', level=3)
        build_temp = pathlib.Path(self.build_temp)
        build_temp.mkdir(parents=True, exist_ok=True)
        extension_path = pathlib.Path(self.get_ext_fullpath(extension.name))
        extension_path.mkdir(parents=True, exist_ok=True)

        self.announce('Configuring CMake project', level=3)
        self.spawn(
            [
                'cmake',
                f'-H{source_directory}',
                f'-B{self.build_temp}',
                f'-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extension_path.parent.absolute()}',
                f'-DCMAKE_BUILD_TYPE={"Debug" if self.debug else "Release"}',
            ]
        )

        if not self.dry_run:
            self.announce('Building binaries', level=3)
            self.spawn(
                [
                    'cmake',
                    '--build',
                    self.build_temp,
                ]
            )


setuptools.setup(
    name='PyCompiledNN',
    use_scm_version=True,
    setup_requires=['setuptools_scm'],
    packages=[],
    description='Python Bindings for CompiledNN',
    long_description=open('./README.md', 'r').read(),
    long_description_content_type='text/markdown',
    license='MIT',
    ext_modules=[CMakeExtension(name='PyCompiledNN')],
    cmdclass={
        'build_ext': BuildCMakeExt,
    },
)
