FOLDER=$HOME/'Documentos'
SUBFOLDER='ttbar_CR4/'

echo $FOLDER/$SUBFOLDER

ls $FOLDER/$SUBFOLDER > root.in

rm input.in
for x in `cat root.in` ; do
echo Creating $x ...
ls $FOLDER/$SUBFOLDER$x >> input.in
done

mkdir -p results

