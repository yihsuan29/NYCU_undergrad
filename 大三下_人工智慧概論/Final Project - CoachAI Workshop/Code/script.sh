model_path="./model/test19_ShuttleNet_hyp_epoch_450_dim_8/"
python train.py --output_folder_name ${model_path} --model_type ShuttleNet --encode_length 4 --seed_value 42 --epoch 450
python generator.py ${model_path} 