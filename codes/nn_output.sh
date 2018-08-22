[38;2;74;176;245m [1mProfile [0m   Starting  [1m@main [0m]
[38;2;74;176;245m [1mProfile [0m   .. Starting  [1mInitialisation [0m
[38;2;74;176;245m [1mProfile [0m   .... Starting  [1m@initialise [0m
[38;2;74;176;245m [1mProfile [0m   .... Time elapsed in  [1m@initialise [0m: ..............................  [1m0.0s [0m
[38;2;74;176;245m [1mProfile [0m   .... Starting  [1m@initialise_backend [0m
[38;2;74;176;245m [1mProfile [0m   ...... Starting  [1m@configure_tensorflow [0m
[38;2;74;176;245m [1mProfile [0m   ...... Time elapsed in  [1m@configure_tensorflow [0m: ..................  [1m3.8s [0m
[38;2;74;176;245m [1mProfile [0m   .... Time elapsed in  [1m@initialise_backend [0m: ......................  [1m4.1s [0m
{'config': './configs/default.json',
    'devices': 1,
    'folds': 3,
    'gpu': False,
    'input': './input/',
     'jobname': '',
     'mode': 'cpu',
     'optimise_adversarial': False,
     'optimise_classifier': False,
     'output': './output/',
     'patches': [],
     'tensorboard': False,
     'theano': False,
     'train': True,
     'train_adversarial': False,
     'train_classifier': False,
     'verbose': False}
{u'adversary': {u'compile': {},
                u'fit': {},
                u'model': {u'architecture': [{}],
                           u'default': {u'activation': u'relu',
                                        u'units': 64},
                           u'gmm_components': 20}},
 u'classifier': {u'compile': {u'loss': u'binary_crossentropy',
                              u'optimizer': <keras.optimizers.Adam object at 0x7f364330a490>},
                 u'fit': {u'batch_size': 8192,
                          u'epochs': 200,
                          u'shuffle': True,
                          'verbose': 2},
                 u'model': {u'architecture': [{}, {}, {}],
                            u'default': {u'activation': u'relu',
                                         u'batchnorm': True,
                                         u'units': 64}}},
 u'combined': {u'compile': {u'loss': [u'binary_crossentropy', None],
                            u'loss_weights': [1.818181818181818e-08, 1.0],
                            u'optimizer': <keras.optimizers.Adam object at 0x7f364330a4d0>},
               u'fit': {u'batch_size': 8192,
                        u'epochs': 200,
                        u'shuffle': True,
                        'verbose': 2},
               u'model': {u'lambda_reg': 10.0,
                          u'lr_ratio': 1.818181818181818e-08},
               u'pretrain': 10}}
  TensorFlow version: 1.4.1
 [38;2;74;176;245m [1mProfile [0m   .. Time elapsed in  [1mInitialisation [0m: .............................  [1m4.2s [0m
 [38;2;74;176;245m [1mProfile [0m   .. Starting  [1m@load_data [0m
 [38;2;74;176;245m [1mProfile [0m   .. Time elapsed in  [1m@load_data [0m: ...............................  [1m103.8s [0m
 [38;2;74;176;245m [1mProfile [0m   .. Starting  [1m@get_decorrelation_variables [0m
 [38;2;74;176;245m [1mProfile [0m   .. Time elapsed in  [1m@get_decorrelation_variables [0m: ...............  [1m0.1s [0m
 [38;2;74;176;245m [1mProfile [0m   .. Starting  [1mClassifier-only fit, cross-validation [0m
 [38;2;74;176;245m [1mProfile [0m   .. Time elapsed in  [1mClassifier-only fit, cross-validation [0m: ......  [1m3.3s [0m
 [38;2;74;176;245m [1mProfile [0m   .. Starting  [1mClassifier-only fit, full [0m
Epoch 1/200
 - 30s - loss: 0.3754
Epoch 2/200
 - 30s - loss: 0.3607
 ...
Epoch 199/200
 - 15s - loss: 0.3391
Epoch 200/200
 - 14s - loss: 0.3390
 [38;2;74;176;245m [1mProfile [0m   .. Time elapsed in  [1mClassifier-only fit, full [0m: ...............  [1m3022.6s [0m
 [38;2;74;176;245m [1mProfile [0m   .. Starting  [1mCombined adversarial fit, cross-validation [0m
 [38;2;74;176;245m [1mProfile [0m   .. Time elapsed in  [1mCombined adversarial fit, cross-validation [0m: .  [1m0.1s [0m
 [38;2;74;176;245m [1mProfile [0m   .. Starting  [1mCombined adversarial fit, full [0m
Epoch 1/10
 - 20s - loss: -4.3951e-01 - classifier_loss: 0.3389 - adversary_loss: -4.3951e-01
Epoch 2/10
 - 19s - loss: -5.3614e-01 - classifier_loss: 0.3388 - adversary_loss: -5.3614e-01
...
 - 21s - loss: -5.8501e-01 - classifier_loss: 0.3388 - adversary_loss: -5.8501e-01
Epoch 10/10
 - 22s - loss: -5.8515e-01 - classifier_loss: 0.3388 - adversary_loss: -5.8515e-01

Epoch 1/200
 - 33s - loss: -4.1862e-01 - classifier_loss: 0.3887 - adversary_loss: -4.1862e-01
Epoch 2/200
 - 29s - loss: -3.7337e-01 - classifier_loss: 0.4342 - adversary_loss: -3.7337e-01
...
Epoch 199/200
 - 30s - loss: -3.5192e-01 - classifier_loss: 0.4600 - adversary_loss: -3.5192e-01
Epoch 200/200
 - 29s - loss: -3.5205e-01 - classifier_loss: 0.4600 - adversary_loss: -3.5205e-01
 [38;2;74;176;245m [1mProfile [0m   .. Time elapsed in  [1mCombined adversarial fit, full [0m: ..........  [1m6147.7s [0m
 [38;2;74;176;245m [1mProfile [0m   Time elapsed in  [1m@main [0m: ......................................  [1m9284.2s [0m
